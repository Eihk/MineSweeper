#include "MineSweeper.h"

MineSweeper::MineSweeper() : _Window(nullptr), _Renderer(nullptr), GameState(EGameState::EGS_Menu),
    _GameDifficulty({0, 0, 0}){

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL could not initialise! SDL_Error: "
        << SDL_GetError() << std::endl;
	}

    if (TTF_Init() < 0) {
        std::cout << "SDL_ttf could not initialise! Error: " << TTF_GetError() << std::endl;
    }

    /* Initialize Window and Renderer */
    _Window = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, MenuScreenWidth, MenuScreenHeight,
    SDL_WINDOW_SHOWN);
    _Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_SOFTWARE);
}

void MineSweeper::MenuScreen(){
    SDL_SetWindowSize(_Window, MenuScreenWidth, MenuScreenHeight);
    SDL_SetWindowPosition(_Window, SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED);

    Menu _Menu = Menu(_Renderer, MenuScreenWidth, MenuScreenHeight);

    auto HandleDifficulty = [&](const GameDifficulty& Difficulty){
        _GameDifficulty = Difficulty;
        GameState = EGameState::EGS_Board;
    };

	while (GameState == EGameState::EGS_Menu){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				GameState = EGameState::EGS_Exit;
			}
            if(event.type == SDL_MOUSEBUTTONDOWN){
                _Menu.HandleMouseClick(event, HandleDifficulty);
            }
			if (event.type == SDL_WINDOWEVENT
				&& event.window.event == SDL_WINDOWEVENT_CLOSE
				&& event.window.windowID == SDL_GetWindowID(_Window)){
				GameState = EGameState::EGS_Exit;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
				GameState = EGameState::EGS_Exit;
			}
		}
        
        _Menu.Render(_Renderer);
        SDL_RenderPresent(_Renderer);

        SDL_Delay(20);
    }
}

void MineSweeper::BoardScreen(){
    SDL_RenderClear(_Renderer);
    const int BoardScreenWidth = _GameDifficulty.Cols * (CellSize + CellGap) + CellGap;
    const int BoardScreenHeight = _GameDifficulty.Rows * (CellSize + CellGap) + CellGap + 120;

    Board _Board = Board(_Renderer, _GameDifficulty);

    SDL_SetWindowSize(_Window, BoardScreenWidth, BoardScreenHeight);
    SDL_SetWindowPosition(_Window, SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED);

    auto HandleClick = [&](Cell& _Cell){
        if(_Cell.GetCellState() == ECellState::ECS_Unflipped){
            _Cell.FlipCell();
            _Cell.Render(_Renderer);
        }
    };

    while(GameState == EGameState::EGS_Board){
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				GameState = EGameState::EGS_Exit;
			}
            if(event.type == SDL_MOUSEBUTTONDOWN){
                _Board.HandleMouseClick(event, HandleClick);
            }
			if (event.type == SDL_WINDOWEVENT
				&& event.window.event == SDL_WINDOWEVENT_CLOSE
				&& event.window.windowID == SDL_GetWindowID(_Window)){
				GameState = EGameState::EGS_Exit;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
				GameState = EGameState::EGS_Exit;
			}
		}
        SDL_SetRenderDrawColor(_Renderer, 114, 166, 176, 255);
        SDL_RenderClear(_Renderer);
        _Board.RenderBoard(_Renderer);
        SDL_RenderPresent(_Renderer);
        SDL_Delay(20);
    }
}

void MineSweeper::Play(){
    while(GameState != EGameState::EGS_Exit){
        switch ((GameState))
        {
        case EGameState::EGS_Menu:
            MenuScreen();
            break;
        case EGameState::EGS_Board:
            BoardScreen();
            break;
        default:
            break;
        }
    }
}

MineSweeper::~MineSweeper(){
    /* Destriy Window and Renderer */
    SDL_DestroyRenderer(_Renderer);
	SDL_DestroyWindow(_Window);
    _Window = nullptr;
    _Renderer = nullptr;
	SDL_Quit();
}