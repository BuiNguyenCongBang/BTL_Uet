#include "CommonFunc.h"
#include "BaseObject.h"
#include "ThreatObject.h"
#include "ThreatObject2.h"
#include "ImpTimer.h"
#include "MainObject.h"
#include "sound.h"
#include <iostream>
#include "Text.h"


BaseObject g_background;
BaseObject g_startgame1;
BaseObject g_startgame2;
BaseObject g_lossgame;
BaseObject g_restartgame;
BaseObject g_wall_object;
BaseObject g_suppermine_object;
BaseObject g_mine_object;




bool InitData()
{
    bool success = 1;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game SDL",                //tên cửa sổ
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,    //kích thước 
        SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = 0;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = 0;
        }
        else SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) && imgFlags))   success = 0;
    }

    return success;
}

bool LoadMedia()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return false;
    }
    if (CheckSound == false)
    {
        return false;
    }
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//mapreal.png", g_screen);
    if (ret = false) return false;
    return true;
}

bool LoadStartGame1()
{
    bool ret = g_startgame1.LoadImg("img//startgame1.png", g_screen);
    if (ret = false) return false;
    return true;
}

bool LoadStartGame2()
{
    bool ret = g_startgame2.LoadImg("img//startgame2.png", g_screen);
    if (ret = false) return false;
    return true;
}

bool LoadGame(BaseObject base, std::string path,int x,int y){
    bool ret = base.LoadImg(path, g_screen);
    SDL_Rect renderQuad = { x, y, base.GetRect().w, base.GetRect().h};

    SDL_RenderCopy(g_screen, base.GetTexture(), NULL, &renderQuad);
    return ret;
}

bool LoadRestartGame() {
    bool ret = g_restartgame.LoadImg("img//restart.png", g_screen);
    SDL_Rect renderQuad = { 0, 140, g_restartgame.GetRect().w, g_restartgame.GetRect().h };

    SDL_RenderCopy(g_screen, g_restartgame.GetTexture(), NULL, &renderQuad);
    return ret;
}



int readHighScore() {
    int highScore = 0;
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    return highScore;
}

void writeHighScore(int score) {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    }
}



void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

#undef main
int main(int argc, char* argv[])
{
    std::cout << 2 << std::endl;

    ImpTimer fps_timer;
    std::cout << 1 << std::endl;
    if (InitData() == false)
    {
        //return -1;
    }
    if (LoadBackground() == false)
    {
        //return -1;
    }
    if (LoadStartGame1() == false)
    {
        //return -1;
    }
    if (LoadStartGame2() == false)
    {
        //return -1;
    }
    if (LoadGame(g_lossgame, "img//LossGame.png", 0, 140) == false)
    {
        //return -1;
    }
    if (LoadMedia() == false)
    {
        //return -1;
    }

    std::cout << "false" << std::endl;
    bool is_quit = false;
    bool start_game = 0;
    std::vector<int> time_loss_game;

    int load_startgame = 1;

    

    MixBackGround();

    while (!start_game)
    {
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        if (load_startgame == 1)
        {
            g_startgame1.Render(g_screen, NULL);
        }
        else if (load_startgame == 2)
        {
            g_startgame2.Render(g_screen, NULL);
        }

        int x = 0, y = 0;
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
            
                if (g_event.button.button == SDL_BUTTON_LEFT)
                {
                    Uint32 buttons = SDL_GetMouseState(&x, &y);

                    //std::cout << x << " " << y << std::endl;
                    if (x >= 539 && x <= 732 && y >= 416 && y <= 570)
                    {
                        load_startgame = 2;
                    }
                    else
                    {
                        load_startgame = 1;
                    }

                    if (load_startgame == 1)
                    {
                        g_startgame1.Render(g_screen, NULL);
                    }
                    else if (load_startgame == 2)
                    {
                        g_startgame2.Render(g_screen, NULL);
                        start_game = 1;
                        MixSelect();
                        break;
                    }
                }
            }
        }
        SDL_RenderPresent(g_screen);

    }




    MainObject p_player;
    p_player.set_hp(100);
    p_player.set_mp(0);
    p_player.LoadImg("img//MainReal.png", g_screen);
    p_player.set_clips();

    float Y_THREAT1S_ROUND_1[NUM_THREAT1S_ROUND_1] = { 1, 1.3, 1.4, 2, 2.1};
    float Y_THREAT2S_ROUND_1[NUM_THREAT2S_ROUND_1] = { 1.5, 2.3};
    float Y_THREAT1S_ROUND_2[NUM_THREAT1S_ROUND_2] = { 3.3, 3.5, 3.7, 4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.2, 5.4, 5.8, 6, 6.2, 6.4, 6.45, 6.5, 6.55, 6.6, 6.8};
    float Y_THREAT2S_ROUND_2[NUM_THREAT2S_ROUND_2] = { 3.4, 3.8, 4.5, 5, 5.1, 5.8, 6.5, 6.6, 6.65, 6.8};
    float Y_THREAT1S_ROUND_3[NUM_THREAT1S_ROUND_3] = { 7.2, 7.4, 7.5, 7.6, 7.65, 7.65, 7.7, 7.8, 7.85, 7.85, 7.9, 7.9, 7.9, 8,
                                                       8.3, 8.6, 8.8, 9.3, 9.5, 9.55, 9.55, 9.55, 9.6, 9.6, 9.6};
    float Y_THREAT2S_ROUND_3[NUM_THREAT2S_ROUND_3] = { 7.2, 7.3, 7.35, 7.4, 7.6, 7.9, 8, 8.5, 9, 9.3, 9.5, 9.55, 9.55, 9.6, 9.6, 9.6, 9.65, 9.65};
    float Y_THREAT1S_ROUND_4[NUM_THREAT1S_ROUND_4] = { 10, 10.3, 10.4, 10.6, 10.6, 10.61, 10.63, 10.65, 10.65, 10.65, 
                                                       10.67, 10.68, 10.68, 10.69, 10.69, 10.7, 10.7, 10.71, 10.72, 10.72, 10.73, 10.73, 
                                                       10.74, 10.75, 10.75 , 10.76 , 10.76, 10.77 , 10.77, 10.78, 10.78 , 10.79, 10.8, 10.81, 
                                                       10.82, 10.84 , 10.85, 10.86, 10.87, 10.9 };
    float Y_THREAT2S_ROUND_4[NUM_THREAT2S_ROUND_4] = { 10.1, 10.35, 10.55, 10.58, 10.6, 10.6, 10.61, 10.62, 10.63, 10.63, 10.65, 10.65, 10.65, 10.65, 10.75, 10.76 , 10.76, 10.77 , 10.77, 10.78, 10.78 , 10.79, 10.8, 10.81,
                                                       10.82, 10.83, 10.84 , 10.85, 10.86, 10.87 };

    ThreatObject* p_threat = new ThreatObject[NUM_THREAT1S];
    ThreatObject2* p_threat2 = new ThreatObject2[NUM_THREAT2S];
    /*
    for (int i = 0; i < NUM_THREAT1S; i++)
    {
        ThreatObject* p_threat_ = p_threat + i;
        bool ret = p_threat_->LoadImg("img//SkeletonWalkRealReal.png", g_screen);
        p_threat_->set_clips();
        p_threat_->set_speed(5);
        int randy = rand() % 5 + 1;
        p_threat_->SetRect(SCREEN_WIDTH * (i + 1), (randy - 1) * 64 + 144);
    }*/
    
    /*for (int i = 0; i < NUM_THREAT2S; i++)
    {
        ThreatObject2* p_threat2_ = p_threat2 + i;
        bool ret = p_threat2_->LoadImg("img//goku_left.png", g_screen);
        p_threat2_->set_clips();
        p_threat2_->set_speed(7);
        int randy = rand() % 5 + 1;
        p_threat2_->SetRect(SCREEN_WIDTH * (i+1), (randy - 1) * 64 + 144);
    }*/

    //round1

    for (int i = 0; i < NUM_THREAT1S_ROUND_1; i++)
    {
        ThreatObject* p_threat_ = p_threat + i;
        bool ret = p_threat_->LoadImg("img//SkeletonWalkRealReal.png", g_screen);
        p_threat_->set_clips();
        p_threat_->set_speed(5);
        int randy = rand() % 5 + 1;
        int x = Y_THREAT1S_ROUND_1[i] * SCREEN_WIDTH;
        p_threat_->SetRect(x, (randy - 1) * 64 + 144);
    }

    for (int i = 0; i < NUM_THREAT2S_ROUND_1; i++)
    {
        ThreatObject2* p_threat2_ = p_threat2 + i;
        bool ret = p_threat2_->LoadImg("img//goku_left.png", g_screen);
        p_threat2_->set_clips();
        p_threat2_->set_speed(7);

        int randy = rand() % 5 + 1;
        int x = Y_THREAT2S_ROUND_1[i] * SCREEN_WIDTH;
        p_threat2_->SetRect(x, (randy - 1) * 64 + 144);
    }

    //Round2

    for (int i = NUM_THREAT1S_ROUND_1; i < NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2; i++)
    {
        ThreatObject* p_threat_ = p_threat + i;
        bool ret = p_threat_->LoadImg("img//SkeletonWalkRealReal.png", g_screen);
        p_threat_->set_clips();
        p_threat_->set_speed(7);
        int randy = rand() % 5 + 1;
        p_threat_->SetRect(Y_THREAT1S_ROUND_2[i - NUM_THREAT1S_ROUND_1] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
    }

    for (int i = NUM_THREAT2S_ROUND_1; i < NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2; i++)
    {

        ThreatObject2* p_threat2_ = p_threat2 + i;
        bool ret = p_threat2_->LoadImg("img//goku_left.png", g_screen);
        p_threat2_->set_clips();
        p_threat2_->set_speed(9);

        int randy = rand() % 5 + 1;

        int x = Y_THREAT2S_ROUND_2[i - NUM_THREAT2S_ROUND_1] * SCREEN_WIDTH;
        p_threat2_->SetRect(x, (randy - 1) * 64 + 144);
    }

    //Round3
    for (int i = NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2; i < NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2 + NUM_THREAT1S_ROUND_3; i++)
    {
        ThreatObject* p_threat_ = p_threat + i;
        bool ret = p_threat_->LoadImg("img//SkeletonWalkRealReal.png", g_screen);
        p_threat_->set_clips();
        p_threat_->set_speed(9);
        int randy = rand() % 5 + 1;
        p_threat_->SetRect(Y_THREAT1S_ROUND_3[i- NUM_THREAT1S_ROUND_1 - NUM_THREAT1S_ROUND_2] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
    }

    for (int i = NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2; i < NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2 + NUM_THREAT2S_ROUND_3; i++)
    {

        ThreatObject2* p_threat2_ = p_threat2 + i;
        bool ret = p_threat2_->LoadImg("img//goku_left.png", g_screen);
        p_threat2_->set_clips();
        p_threat2_->set_speed(11);

        int randy = rand() % 5 + 1;
        p_threat2_->SetRect(Y_THREAT2S_ROUND_3[i - NUM_THREAT2S_ROUND_1 - NUM_THREAT2S_ROUND_2] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
    }
    
    //Round4
    for (int i = NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2 + NUM_THREAT1S_ROUND_3; i < NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2 + NUM_THREAT1S_ROUND_3 +  NUM_THREAT1S_ROUND_4; i++)
    {
        ThreatObject* p_threat_ = p_threat + i;
        bool ret = p_threat_->LoadImg("img//SkeletonWalkRealReal.png", g_screen);
        p_threat_->set_clips();
        p_threat_->set_speed(11);
        int randy = rand() % 5 + 1;
        p_threat_->SetRect(Y_THREAT1S_ROUND_4[i - NUM_THREAT1S_ROUND_1 - NUM_THREAT1S_ROUND_2 - NUM_THREAT1S_ROUND_3] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
    }

    for (int i = NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2 + NUM_THREAT2S_ROUND_3; i < NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2 + NUM_THREAT2S_ROUND_3 + NUM_THREAT2S_ROUND_4; i++)
    {

        ThreatObject2* p_threat2_ = p_threat2 + i;
        bool ret = p_threat2_->LoadImg("img//goku_left.png", g_screen);
        p_threat2_->set_clips();
        p_threat2_->set_speed(13);

        int randy = rand() % 5 + 1;
        p_threat2_->SetRect(Y_THREAT2S_ROUND_4[i - NUM_THREAT2S_ROUND_1 - NUM_THREAT2S_ROUND_2 - NUM_THREAT2S_ROUND_3] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
    }


    while (!is_quit)
    {
        fps_timer.start();

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandleInputAction(g_event, g_screen);
        } 

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);
      
        if (p_player.get_hp() > 0)
        {
            for (int i = 0; i < NUM_THREAT2S; i++)
            {
                ThreatObject2* p_threat2_ = p_threat2 + i;
                p_threat2_->DoPlayer();
                if (p_threat2_->GetRect().y < 1400)
                {
                    p_threat2_->set_clips();
                    p_threat2_->Show(g_screen);
                    p_threat2_->set_success_attack(false);
                    p_threat2_->ShowBullet(g_screen);
                    p_threat2_->random_increase_hp(g_screen);

                    if (p_threat2_->get_success_attack() == true)
                    {
                        p_player.set_hp(p_player.get_hp() - 5);
                        p_threat2_->set_success_attack(false);
                    }
                }
            }

            for (int i = 0; i < NUM_THREAT1S; i++)
            {
                ThreatObject* p_threat_ = p_threat + i;
                p_threat_->DoPlayer();
                if (p_threat_->GetRect().y < 1400)
                {
                    //p_player.HandleHp(*p_threat_);

                    if (p_threat_->get_attack() == true)
                    {
                        p_player.set_hp(p_player.get_hp() - 2);
                        p_threat_->set_attack(false);
                    }
                    p_threat_->set_clips();
                    p_threat_->Show(g_screen);
                    p_threat_->random_increase_hp(g_screen);
                }

            }
        }
        
        

        p_player.HandleBullet(g_screen, p_threat, NUM_THREAT1S, p_threat2, NUM_THREAT2S);
        p_player.show_hp(g_screen);
        p_player.show_mp(g_screen);
        p_player.Show(g_screen);


        TextObj Coin_txt;
        TTF_Font* font_common;
        TTF_Font* font_common1;
        TTF_Font* font_common2;
        font_common = TTF_OpenFont("font//ObelixProB-cyr.ttf", 20);
        font_common1 = TTF_OpenFont("font//ObelixProB-cyr.ttf", 30);
        font_common2 = TTF_OpenFont("font//ObelixProB-cyr.ttf", 70);
        
        if (TTF_Init() == -1)
        {
            std::cout << "false" << std::endl;
            return -1;
        }
        

        p_player.SetPoint(p_threat, NUM_THREAT1S, p_threat2, NUM_THREAT2S);
        int g_point_ = p_player.get_point();
        Coin_txt.SetColor(1);
        std::string show_money = std::to_string(g_point_);
        Coin_txt.SetText(show_money);
        Coin_txt.LoadFromRenderText(font_common1, g_screen);
        Coin_txt.RenderText(g_screen, 170, 25);









        if (p_player.get_hp() <= 0)
        {
            LoadGame(g_lossgame, "img//LossGame.png", 0, 140);

            int highScore = readHighScore();
            //std::cout << highScore << std::endl;
            int currentScore = p_player.get_point();
            if (currentScore > highScore)
            {
                highScore = currentScore;
                writeHighScore(highScore);
            }
            TextObj g_score;
            TextObj g_high_score;
            TextObj g_time_loss_game;
            g_score.SetColor(1);
            std::string Score = std::to_string(currentScore);
            std::string show_score = "YOUR SCORE: " + Score;
            g_score.SetText(show_score);
            g_score.LoadFromRenderText(font_common1, g_screen);
            g_score.RenderText(g_screen, 300, 320);

            g_high_score.SetColor(1);
            std::string High_Score = std::to_string(highScore);
            std::string show_high_score = "HIGH SCORE: " + High_Score;
            g_high_score.SetText(show_high_score);
            g_high_score.LoadFromRenderText(font_common1, g_screen);
            g_high_score.RenderText(g_screen, 300, 380);
            
            
            //int time_ = SDL_GetTicks();
            ////std::cout << time_loss_game.size() << std::endl;
            //if (time_loss_game.size() == 0)
            //{
            //    time_loss_game.push_back(time_);
            //}
            /*else if (time_ - time_loss_game[time_loss_game.size() - 1] >= 60000)
            {
                time_loss_game.push_back(time_);
            }*/
            /*std::cout << time_ << " " << time_loss_game[0] << " " << (time_ - time_loss_game[0]) / 1000 << std::endl;
            
            int time_now = 10 - (time_ - time_loss_game[0]) / 1000;
            if (time_now >= 0)
            {
                //std::cout << "aaaaaaaaaaaaaaaaaaaa" << std::endl;
                g_time_loss_game.SetColor(1);
                std::string show_time_ = std::to_string(time_now);
                g_time_loss_game.SetText(show_time_);
                g_time_loss_game.LoadFromRenderText(font_common2, g_screen);
                g_time_loss_game.RenderText(g_screen, 180, 330);
            }
            else
            {
                is_quit = true;
            }*/
            


            if (p_player.get_x_mouse() >= 104 && p_player.get_x_mouse() <= 250 && p_player.get_y_mouse() >= 300 && p_player.get_y_mouse() <= 424)
            {
                p_player.set_hp(100);
                p_player.set_mp(0);
                p_player.set_supper_shot(false);
                p_player.set_point(0);
                p_player.LoadImg("img//MainReal.png", g_screen);
                p_player.set_clips();

                for (int i = 0; i < NUM_THREAT1S; i++)
                {
                    ThreatObject* p_threat_ = p_threat + i;
                    
                    p_threat_->set_move(true);
                    int randy = rand() % 5 + 1;
                    p_threat_->SetRect(SCREEN_WIDTH * (i + 0.5), (randy - 1) * 64 + 144);
                }

                for (int i = 0; i < NUM_THREAT2S; i++)
                {
                    ThreatObject2* p_threat2_ = p_threat2 + i;

                    p_threat2_->set_move(true);
                    p_threat2_->set_x_bullet(590);
                    int randy = rand() % 5 + 1;
                    p_threat2_->SetRect(SCREEN_WIDTH * (i + 1), (randy - 1) * 64 + 144);
                }

                //round1

                for (int i = 0; i < NUM_THREAT1S_ROUND_1; i++)
                {
                    ThreatObject* p_threat_ = p_threat + i;
                    
                    p_threat_->set_speed(5);
                    int randy = rand() % 5 + 1;
                    int x = Y_THREAT1S_ROUND_1[i] * SCREEN_WIDTH;
                    p_threat_->SetRect(x, (randy - 1) * 64 + 144);
                }

                for (int i = 0; i < NUM_THREAT2S_ROUND_1; i++)
                {
                    ThreatObject2* p_threat2_ = p_threat2 + i;
                    
                    p_threat2_->set_speed(7);

                    int randy = rand() % 5 + 1;
                    int x = Y_THREAT1S_ROUND_2[i] * SCREEN_WIDTH;
                    p_threat2_->SetRect(x, (randy - 1) * 64 + 144);
                }

                //Round2

                for (int i = NUM_THREAT1S_ROUND_1; i < NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2; i++)
                {
                    ThreatObject* p_threat_ = p_threat + i;
                 
                    p_threat_->set_speed(7);
                    int randy = rand() % 5 + 1;
                    p_threat_->SetRect(Y_THREAT1S_ROUND_2[i - NUM_THREAT1S_ROUND_1] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
                }

                for (int i = NUM_THREAT2S_ROUND_1; i < NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2; i++)
                {

                    ThreatObject2* p_threat2_ = p_threat2 + i;
                   
                    p_threat2_->set_speed(9);

                    int randy = rand() % 5 + 1;

                    int x = Y_THREAT2S_ROUND_2[i - NUM_THREAT2S_ROUND_1] * SCREEN_WIDTH;
                    p_threat2_->SetRect(x, (randy - 1) * 64 + 144);
                }

                //Round3
                for (int i = NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2; i < NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2 + NUM_THREAT1S_ROUND_3; i++)
                {
                    ThreatObject* p_threat_ = p_threat + i;
                   
                    p_threat_->set_speed(9);
                    int randy = rand() % 5 + 1;
                    p_threat_->SetRect(Y_THREAT1S_ROUND_3[i - NUM_THREAT1S_ROUND_1 - NUM_THREAT1S_ROUND_2] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
                }

                for (int i = NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2; i < NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2 + NUM_THREAT2S_ROUND_3; i++)
                {

                    ThreatObject2* p_threat2_ = p_threat2 + i;
                    p_threat2_->set_speed(11);

                    int randy = rand() % 5 + 1;
                    p_threat2_->SetRect(Y_THREAT2S_ROUND_3[i - NUM_THREAT2S_ROUND_1 - NUM_THREAT2S_ROUND_2] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
                }

                //Round4
                for (int i = NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2 + NUM_THREAT1S_ROUND_3; i < NUM_THREAT1S_ROUND_1 + NUM_THREAT1S_ROUND_2 + NUM_THREAT1S_ROUND_3 + NUM_THREAT1S_ROUND_4; i++)
                {
                    ThreatObject* p_threat_ = p_threat + i;
                    
                    p_threat_->set_speed(11);
                    int randy = rand() % 5 + 1;
                    p_threat_->SetRect(Y_THREAT1S_ROUND_4[i - NUM_THREAT1S_ROUND_1 - NUM_THREAT1S_ROUND_2 - NUM_THREAT1S_ROUND_3] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
                }

                for (int i = NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2 + NUM_THREAT2S_ROUND_3; i < NUM_THREAT2S_ROUND_1 + NUM_THREAT2S_ROUND_2 + NUM_THREAT2S_ROUND_3 + NUM_THREAT2S_ROUND_4; i++)
                {

                    ThreatObject2* p_threat2_ = p_threat2 + i;
                    bool ret = p_threat2_->LoadImg("img//goku_left.png", g_screen);
                    p_threat2_->set_clips();
                    p_threat2_->set_speed(13);

                    int randy = rand() % 5 + 1;
                    p_threat2_->SetRect(Y_THREAT2S_ROUND_4[i - NUM_THREAT2S_ROUND_1 - NUM_THREAT2S_ROUND_2 - NUM_THREAT2S_ROUND_3] * SCREEN_WIDTH, (randy - 1) * 64 + 144);
                }

                p_player.set_mouse(90, 220);

                
                SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(g_screen);
            }
        }


        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time > 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }

    close();

    return 0;
}