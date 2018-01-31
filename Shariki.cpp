#include "TXLib.h"

struct Ball
    {
    int x, y, vx, vy;
    int radiys;
    int red, green, blue;
    int up, down, radiysP, radiysM;

    void Physical(double dt);
    void Ctrl();
    void Draw();
    };

double Distancs(Ball b1, Ball b2);
int Collision(Ball b1, Ball b2);
void Start(char text [], HDC Fon);

void MoveBall();

int main()
    {
    txCreateWindow (800, 600);
    MoveBall ();
    }

void MoveBall()
    {
    int score = 0;
    double dt = 0.2;
    int TimePc = GetTickCount();

    Ball b[6] = { {  1,   1, 4, 4, 25,  255, 0, 255,   'Q', 'A', 'Z', VK_F1},
                  {236, 172, 6, 6, 25,  0, 255, 0,     'W', 'S', 'X', VK_F2},
                  {428, 230, 9, 6, 25,  0, 0, 255,     'E', 'D', 'C', VK_F3},
                  {694, 462, 7, 9, 25,  255, 0, 0,     'R', 'F', 'V', VK_F4},
                  {156, 379, 8, 8, 25,  255, 255, 0,   'T', 'G', 'B', VK_F5},
                  {356, 524, 7, 4, 25,  255, 255, 255, 'Y', 'H', 'N', VK_F6} };

    HDC Fon = txLoadImage("Шарик.BMP");
    Start("Press 1 for playing", Fon);
    txDeleteDC(Fon);


 //   txSetFillColor (TX_RED);
 //   txSetColor (TX_NULL);
    while (score < 100)
        {
        int TimeStart = (GetTickCount() - TimePc) / 1000;

        if (TimeStart > 30) break;
        if (score >= 30) break;


        printf("Score = %d\n", score);
        printf("Time = %d\n", TimeStart);

        txSetFillColor (TX_YELLOW);
        txClear ();

        int i = 0;
        while (i < 6)
        {
            b[i].Draw();
            i ++;
        }

        i = 0;
        while (i < 6)
        {
            b[i].Physical(dt);
            i ++;
        }

        i = 0;
        while (i < 6)
        {
            b[i].Ctrl();
            i ++;
        }

        i = 1;
        while (i < 6)
        {
            if (Collision (b[0], b[i]) == 1) score ++;
            i ++;
        }

        txSleep(10);

        }
    }
void Start(char text [], HDC Fon)
    {
    txBegin();

    while (!GetAsyncKeyState('1'))
        {
        txBitBlt(0, 0, Fon);

        txSelectFont("AR CARTER", 50);
        txSetColor(TX_RED);
        txDrawText(170, 80, 570, 200, text);

        txSleep(10);
        }

    txEnd();
    }

int Collision(Ball b1, Ball b2)
    {
    double Distans12 = Distancs(b1, b2);
    if (Distans12 <= b1.radiys + b2.radiys) return 1;
    else                                    return 0;
    }

double Distancs(Ball b1, Ball b2)
    {
    int d = sqrt((b1.x - b2.x)*(b1.x - b2.x) + (b1.y - b2.y)*(b1.y - b2.y));
    return d;
    }

void Ball::Physical(double dt)
    {
        this->y = this->y + this->vy * dt;    // (*b).y = b->y
        this->x = this->x + this->vx * dt;

        if (x > 800)

            {
            vx = - vx;
            x = 800;
            }

        if (x < 0)

            {
            vx = - vx;
            x = 0;
            }

        if (y < 0)

            {
            vy = - vy;
            y = 10;
            }

        if (y > 600)

            {
            vy = - vy;
            y = 600;
            }

    }

void Ball::Ctrl()
    {
        if (GetAsyncKeyState(down))

            {
            vy ++;
            }

        if (GetAsyncKeyState(up))

            {
            vy --;
            }

        if (GetAsyncKeyState(radiysP))

            {
            radiys = radiys + 1;
            }

        if (GetAsyncKeyState(radiysM))

            {
            radiys = radiys - 1;
            }

        if (radiys <= 1)
            {
            radiys = 25;
            }

        if (radiys >= 100)
            {
            radiys = 25;
            }

    }

void Ball::Draw()
    {

    txSetColor (TX_NULL);

    double n = 0;
    while (n <= radiys - 1)

        {
                                                         // 255    C        C = 0...c...255
                                                         // --- = ---       n = 0...n...r-1
                                                         // r-1    n        c * (r-1) = 255n
                                                         //                 c = 255n / (r-1)
                                                         //                 c = 255/(r-1) * n
                                                         //                 c = 255/(25-1)
        txSetFillColor (RGB (red * sqrt(n/(radiys-1)),
                            green * sqrt(n/(radiys-1)),
                            blue * sqrt(n/(radiys-1))));
        txCircle(x + n / 7, y - n / 7, radiys - n);
        n = n + 2;
        }

    }
