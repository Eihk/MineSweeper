#include "Board.h"

Board::Board(SDL_Renderer* renderer, const GameDifficulty& GameDifficulty){
    _Rows = GameDifficulty.Rows;
    _Cols = GameDifficulty.Cols;
    _Bombs = GameDifficulty.Bombs;
    _MaxCellsIndex = _Rows * _Cols;
    _Renderer = renderer;

    _CellsToOpen = _Rows * _Cols - _Bombs;

    GenerateCells();
    BoardState = EBoardState::EBS_FirstMove;
}

void Board::GenerateCells()
{
    _Map = new Cell[_Rows * _Cols];
    int xCell = CellGap;
    int yCell = yHud + CellGap;

    for (int row = 0; row < _Rows; row++){
        for (int col = 0; col < _Cols; col++){
            SDL_Rect rect = {xCell, yCell, CellSize, CellSize};
            _Map[GetIndex(row, col)] = Cell(rect, row, col);
            xCell += CellSize + CellGap;
        }
        xCell = CellGap;
        yCell += CellSize + CellGap;
    }
}

void Board::GenerateBombs(const int FirstClickedRow, const int FirstClickedCol){
    while(BombsIndexList.size() != _Bombs){
        AddBomb(FirstClickedRow, FirstClickedCol);
    }
    GenerateNumbers();
}

void Board::AddBomb(const int FirstClickedRow, const int FirstClickedCol){
    std::random_device RandomDevice;
    static std::default_random_engine BombRandomEngine(RandomDevice());
    std::uniform_int_distribution<> Row(0, _Rows - 1);
    std::uniform_int_distribution<> Col(0, _Cols - 1);

    int xFutureBombPos = Row(BombRandomEngine);
    int yFutureBombPos = Col(BombRandomEngine);

    while(!IsCellAvailable(xFutureBombPos, yFutureBombPos, FirstClickedRow, FirstClickedCol)){
        xFutureBombPos = Row(BombRandomEngine);
        yFutureBombPos = Col(BombRandomEngine);
    }

    BombsIndexList.push_back(GetIndex(xFutureBombPos, yFutureBombPos));
    _Map[GetIndex(xFutureBombPos, yFutureBombPos)].ChangeCellType(ECellType::ECT_Bomb);
}

bool Board::IsCellAvailable(const int xFutureBombPos, const int yFutureBombPos, const int FirstClickedRow, const int FirstClickedCol){
    if(BombsIndexList.size() == 0) return true;
    if((xFutureBombPos == FirstClickedRow) && (yFutureBombPos == FirstClickedCol)) return false;
    
    bool IsBombAlreadyThere = false;
    const int FutureBombIndex = GetIndex(xFutureBombPos, yFutureBombPos);
    for (auto& ExistingBombIndex: BombsIndexList){
        if(FutureBombIndex == ExistingBombIndex){
            IsBombAlreadyThere = true;
            break;
        }
    }

    return !IsBombAlreadyThere;
}

void Board::GenerateNumbers(){
    const int MaxNumber = 9;
    const SDL_Color NumbersColor[MaxNumber] =
    {{  0,   0,   0,  0},  //0 = Nothing
    { 20,  57, 168, 255},  //1 = BLUE
    { 20, 148,  18, 255},  //2 = GREEN
    {179,  30,  30, 255},  //3 = RED
    {103,  28, 173, 255},  //4 = PURPLE
    {133,  20,  20, 255},  //5 = MAROON
    {  9, 179, 164, 255},  //6 = TURQUOISE
    {  0,   0,   0, 255},  //7 = BLACK
    {255, 255, 255, 255}}; //8 = WHITE


    int xCell = CellGap;
    int yCell = yHud + CellGap;
    for (int row = 0; row < _Rows; row++){
        for (int col = 0; col < _Cols; col++){
            Cell& CurrentCell = _Map[GetIndex(row, col)];
            if(!(CurrentCell.GetCellType() == ECellType::ECT_Bomb)){
                const int NeighborBombs = GetNeighborBombs(row, col);
                if(NeighborBombs != 0){
                    std::string Str = std::to_string(NeighborBombs);
                    const char* Text = Str.c_str();
                    CurrentCell.AddNumber(_Renderer, Text, NumbersColor[NeighborBombs]);
                    CurrentCell.ChangeCellType(ECellType::ECT_Number);
                }
            }
            xCell += CellSize + CellGap;
        }
        xCell = CellGap;
        yCell += CellSize + CellGap; 
    }
}

int Board::GetNeighborBombs(const int Row, const int Col){
    int BombFound = 0;

    for(int i = -1; i < 2; i++){
        if(!((Row + i < 0) || (Row + i > _Rows - 1))){
            for(int j = -1; j < 2; j++){
                if(!((Col + j < 0) || (Col + j > _Cols - 1))){
                    if(IsBombPlantedAt(Row + i, Col + j)){
                        BombFound++;
                    }
                }
            }
        }
    }
    return BombFound;
}

bool Board::IsBombPlantedAt(const int Row, const int Col){
    return _Map[GetIndex(Row, Col)].GetCellType() == ECellType::ECT_Bomb;
}

int Board::GetIndex(const int row, const int col){
    return row * _Cols + col;
}

void Board::RenderBoard(SDL_Renderer* Renderer, HUD& HUD){

    /* Set HUD Button according to BoardState */
    switch (BoardState)
    {
    case EBoardState::EBS_Lose:
        HUD.SetButtonLostTexture(Renderer);
        break;
    case EBoardState::EBS_Win:
        HUD.SetButtonWinTexture(Renderer);
        break;
    default:
        HUD.SetButtonPlayingTexture(Renderer);
        break;
    }

    int xCell = CellGap;
    int yCell = yHud + CellGap;
    for (int row = 0; row < _Rows; row++){
        for (int col = 0; col < _Cols; col++){
            _Map[GetIndex(row, col)].Render(Renderer);
            xCell += CellSize + CellGap;
        }
        xCell = CellGap;
        yCell += CellSize + CellGap; 
    }
}

void Board::HandleMouseClick(const SDL_Event& event, HUD& HUD){
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);

    int xCell = CellGap;
    int yCell = yHud + CellGap;
    for (int row = 0; row < _Rows; row++){
        for (int col = 0; col < _Cols; col++){
            Cell& CurrentCell = _Map[GetIndex(row, col)];
            if(CurrentCell.IsMouseInside(xMouse, yMouse)){
                HandleCellClick(CurrentCell, event, row, col, HUD);
            }
            xCell += CellSize + CellGap;
        }
        xCell = CellGap;
        yCell += CellSize + CellGap; 
    }
}

void Board::HandleCellClick(Cell &CurrentCell, const SDL_Event &event, const int xMouse, const int yMouse, HUD& Hud){
    if (!(CurrentCell.IsCellOpen())){
        if (event.button.button == SDL_BUTTON_LEFT && !CurrentCell.IsFlagged()){
            if (BoardState == EBoardState::EBS_FirstMove){
                GenerateBombs(xMouse, yMouse);
                BoardState = EBoardState::EBS_Playing;
                Hud._TimerCounter->StartTimer();
            }

            if(BoardState == EBoardState::EBS_Playing){
                if(CurrentCell.IsCellBomb()){
                    ShowAllBombs();
                    BoardState = EBoardState::EBS_Lose;
                    Hud._TimerCounter->StopTimer();
                }
                ExpandFrom(CurrentCell, Hud);
                if(_CellsToOpen == 0){
                    BoardState = EBoardState::EBS_Win;
                }  
            }
        }
        if (event.button.button == SDL_BUTTON_RIGHT){
            if(CurrentCell.IsFlagged()){
                CurrentCell.RemoveFlag();
                Hud._FlagCounter->IncrementCounter();
            } else{
                CurrentCell.GetFlag(_Renderer);
                Hud._FlagCounter->DecrementCounter();
            }
            CurrentCell.Render(_Renderer);
        }
    }
}

void Board::ExpandFrom(Cell& ThisCell, HUD& Hud){
    if(ThisCell.IsCellOpen()) return;

    ThisCell.OpenCell(_Renderer);
    ThisCell.Render(_Renderer);
    _CellsToOpen--;

    if (ThisCell.IsFlagged()){
        ThisCell.RemoveFlag();
        Hud._FlagCounter->IncrementCounter();
    }
    
    if(ThisCell.IsCellNumber()) return;
    if(ThisCell.IsCellNothing()){
        std::vector<int> NeighborCells = GetNeighborCell(ThisCell);
        for(int idx = 0; idx < NeighborCells.size(); idx++){
            ExpandFrom(_Map[NeighborCells[idx]], Hud);
        }
    }
}

std::vector<int> Board::GetNeighborCell(Cell& ThisCell){
    const int Row = ThisCell._Row;
    const int Col = ThisCell._Col;
    std::vector<int> NeighborCell;

    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if(InsideIndexRange(Row +i , Col + j)){
                if(!((Row + i == Row) && (Col + j == Col))){
                    NeighborCell.push_back(GetIndex(Row + i, Col + j));
                }
            }
        }
    }

    return NeighborCell;
}

bool Board::InsideIndexRange(const int Row, const int Col){
    bool InsideRowRange = (Row > -1) && (Row < _Rows);
    bool InsideColRange = (Col > -1) && (Col < _Cols);
    return InsideColRange && InsideRowRange;
}

void Board::ShowAllBombs(){
    for(auto CellIndex: BombsIndexList){
        Cell& CurrentCell = _Map[CellIndex];
        CurrentCell.OpenCell(_Renderer);
        CurrentCell.Render(_Renderer);
    }
}

Board::~Board(){
    _Map = nullptr;
    delete[] _Map;
}