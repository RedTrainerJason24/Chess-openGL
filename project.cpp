//mouse_key.cpp 
#include <GL/glut.h>
#include <stdlib.h>
#include<cmath>
#include <iostream>
using namespace std;

#define   screenHeight  800
#define xoffset  0

//initializat
int lastx = 0;
int lasty = 0;
int lastPiece =  0;
bool whitesTurn = true;
int deltaY;
int deltaX;

int chess_array[8][8] ={
			{ 2, 3, 4, 5, 6, 4, 3, 2},
			{ 1, 1, 1, 1, 1, 1, 1, 1},
			{ 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0},
			{-1,-1,-1,-1,-1,-1,-1,-1},
			{-2,-3,-4,-5,-6,-4,-3,-2}
};

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);	//get white background color
    glColor3f(0.0f, 0.0f, 0.0f);	//set drawing color
    glPointSize(4.0);			//a dot is 4x4
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();			//replace current matrix with identity matrix
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
}

void draw_pawn(int x, int y, int color)
{
    glColor3f(color, color, color);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 20, y + 10);
    glVertex2i(x + 80, y + 10);
    glVertex2i(x + 50, y + 60);//top
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 50, y + 50);
    glVertex2i(x + 70, y + 65);
    glVertex2i(x + 50, y + 80);
    glVertex2i(x + 30, y + 65);
    glEnd();


    glBegin(GL_QUADS);                //draw solid polygon
    glVertex2i(x + 30, y + 50);
    glVertex2i(x + 70, y + 50);
    glVertex2i(x + 70, y + 55);
    glVertex2i(x + 30, y + 55);
    glEnd();

    glFlush();

}

void draw_pawn_outline(int x, int y, int color)
{

    glColor3f(color, color, color);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_LINE_LOOP);                //draw solid polygon
    glVertex2i(x + 20, y + 10);
    glVertex2i(x + 80, y + 10);
    glVertex2i(x + 55, y + 50);
    glVertex2i(x + 45, y + 50);
    glEnd();

    glBegin(GL_LINE_LOOP);                //draw solid polygon
    glVertex2i(x + 30, y + 50);
    glVertex2i(x + 70, y + 50);
    glVertex2i(x + 70, y + 55);
    glVertex2i(x + 30, y + 55);
    glEnd();

    glBegin(GL_LINE_LOOP);                //draw solid polygon
    glVertex2i(x + 30, y + 65);
    glVertex2i(x + 45, y + 55);
    glVertex2i(x + 55, y + 55);
    glVertex2i(x + 70, y + 65);
    glVertex2i(x + 50, y + 80);
    glEnd();

    glFlush();
}

void draw_castle(int x, int y, int color)
{

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);


    glBegin(GL_POLYGON);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 25, y + 20);
    glVertex2i(x + 75, y + 20);
    glVertex2i(x + 75, y + 50);
    glVertex2i(x + 25, y + 50);
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 10, y + 50);
    glVertex2i(x + 90, y + 50);
    glVertex2i(x + 90, y + 70);
    glVertex2i(x + 10, y + 70);
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 10, y + 70);
    glVertex2i(x + 26, y + 70);
    glVertex2i(x + 26, y + 90);
    glVertex2i(x + 10, y + 90);
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 42, y + 70);
    glVertex2i(x + 58, y + 70);
    glVertex2i(x + 58, y + 90);
    glVertex2i(x + 42, y + 90);
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 74, y + 70);
    glVertex2i(x + 90, y + 70);
    glVertex2i(x + 90, y + 90);
    glVertex2i(x + 74, y + 90);
    glEnd();

    glFlush();
}

void draw_castle_outline(int x, int y, int color)
{

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_LINE);


    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_LINE_LOOP);                //draw solid polygon
    glVertex2i(x + 25, y + 20);
    glVertex2i(x + 75, y + 20);
    glVertex2i(x + 75, y + 50);
    glVertex2i(x + 25, y + 50);
    glEnd();

    glBegin(GL_LINE_LOOP);                //draw solid polygon
    glVertex2i(x + 10, y + 50);
    glVertex2i(x + 90, y + 50);
    glVertex2i(x + 90, y + 90);
    glVertex2i(x + 74, y + 90);
    glVertex2i(x + 74, y + 70);
    glVertex2i(x + 58, y + 70);
    glVertex2i(x + 58, y + 90);
    glVertex2i(x + 42, y + 90);
    glVertex2i(x + 42, y + 70);
    glVertex2i(x + 26, y + 70);
    glVertex2i(x + 26, y + 90);
    glVertex2i(x + 10, y + 90);
    glEnd();

    glFlush();
}

void draw_horse(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);

    glBegin(GL_POLYGON);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(x + 20, y + 20);// draws up and down
    glVertex2i(x + 50, y + 20);
    glVertex2i(x + 50, y + 65);
    glVertex2i(x + 20, y + 65);
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 20, y + 65);
    glVertex2i(x + 90, y + 50);
    glVertex2i(x + 70, y + 90);
    glVertex2i(x + 45, y + 90);

    glEnd();
    glFlush();
}

void draw_horse_outline(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 20, y + 20);// draws up and down
    glVertex2i(x + 50, y + 20);
    glVertex2i(x + 50, y + 60);
    glVertex2i(x + 90, y + 50);
    glVertex2i(x + 70, y + 90);
    glVertex2i(x + 45, y + 90);
    glVertex2i(x + 20, y + 65);
    glEnd();

    glBegin(GL_LINE_STRIP);                //draw solid polygon
    glVertex2i(x + 45, y + 80);
    glVertex2i(x + 25, y + 60);
    glVertex2i(x + 25, y + 25);
    glEnd();

    glBegin(GL_LINE_STRIP);                //draw solid polygon
    glVertex2i(x + 70, y + 70);
    glVertex2i(x + 60, y + 75);
    glEnd();

    glFlush();
}

void draw_bishop(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);

    glBegin(GL_POLYGON);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 50, y + 10);
    glVertex2i(x + 90, y + 55);
    glVertex2i(x + 50, y + 90);
    glVertex2i(x + 10, y + 55);

    glEnd();
    glFlush();
}

void draw_bishop_outline(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_POLYGON);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 10, y + 55);
    glVertex2i(x + 40, y + 20);
    glVertex2i(x + 60, y + 20);
    glVertex2i(x + 90, y + 55);
    glVertex2i(x + 50, y + 90);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(x + 30, y + 55);
    glVertex2i(x + 70, y + 55);
    glVertex2i(x + 50, y + 70);
    glVertex2i(x + 50, y + 30);
    glEnd();

    glFlush();
}

void draw_queen(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);

    glBegin(GL_POLYGON);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_TRIANGLES);                //draw solid polygon
    glVertex2i(x + 25, y + 20);
    glVertex2i(x + 45, y + 20);
    glVertex2i(x + 10, y + 90);
    glEnd();

    glBegin(GL_TRIANGLES);                //draw solid polygon
    glVertex2i(x + 25, y + 20);
    glVertex2i(x + 50, y + 20);
    glVertex2i(x + 45, y + 85);
    glEnd();

    glBegin(GL_TRIANGLES);                //draw solid polygon
    glVertex2i(x + 50, y + 20);
    glVertex2i(x + 75, y + 20);
    glVertex2i(x + 55, y + 85);
    glEnd();

    glBegin(GL_TRIANGLES);                //draw solid polygon
    glVertex2i(x + 55, y + 20);
    glVertex2i(x + 75, y + 20);
    glVertex2i(x + 90, y + 90);
    glEnd();


    glFlush();
}



void draw_queen_outline(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_LINE_LOOP);                //draw solid polygon
    glVertex2i(x + 25, y + 20);
    glVertex2i(x + 75, y + 20);
    glVertex2i(x + 90, y + 90);
    glVertex2i(x + 66, y + 45);//
    glVertex2i(x + 55, y + 85);
    glVertex2i(x + 50, y + 20);
    glVertex2i(x + 45, y + 85);
    glVertex2i(x + 34, y + 45);//
    glVertex2i(x + 10, y + 90);
    glEnd();


    glFlush();
}

void draw_king(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(x + 35, y + 20);// draws up and down
    glVertex2i(x + 65, y + 20);
    glVertex2i(x + 65, y + 90);
    glVertex2i(x + 35, y + 90);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(x + 10, y + 50); // draws left to right
    glVertex2i(x + 90, y + 50);
    glVertex2i(x + 90, y + 70);
    glVertex2i(x + 10, y + 70);

    glEnd();
    glFlush();
}

void draw_king_outline(int x, int y, int color)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glColor3f(color, color, color);           //red
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_POLYGON);                //draw solid polygon
    glVertex2i(x + 10, y + 10);// draws base
    glVertex2i(x + 90, y + 10);
    glVertex2i(x + 85, y + 20);
    glVertex2i(x + 15, y + 20);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(x + 35, y + 20);// draws up and down
    glVertex2i(x + 65, y + 20);
    glVertex2i(x + 65, y + 50);
    glVertex2i(x + 90, y + 50);
    glVertex2i(x + 90, y + 70);
    glVertex2i(x + 65, y + 70);
    glVertex2i(x + 65, y + 90);
    glVertex2i(x + 35, y + 90);
    glVertex2i(x + 35, y + 70);
    glVertex2i(x + 10, y + 70);
    glVertex2i(x + 10, y + 50);
    glVertex2i(x + 35, y + 50);

    glEnd();
    glFlush();
}

void place_piece(void)
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 8; y > -1; y--)
        {
            switch (chess_array[y][x])
            {
            case 0:
                break;

            case 1:
                draw_pawn(x * 100, y * 100, 1);
                draw_pawn_outline(x * 100, y * 100, 0);
                break;
            case 2:
                draw_castle(x * 100, y * 100, 1);
                draw_castle_outline(x * 100, y * 100, 0);
                break;
            case 3:
                draw_horse(x * 100, y * 100, 1);
                draw_horse_outline(x * 100, y * 100, 0);
                break;
            case 4:
                draw_bishop(x * 100, y * 100, 1);
                draw_bishop_outline(x * 100, y * 100, 0);
                break;
            case 5:
                draw_queen(x * 100, y * 100, 1);
                draw_queen_outline(x * 100, y * 100, 0);
                break;
            case 6:
                draw_king(x * 100, y * 100, 1);
                draw_king_outline(x * 100, y * 100, 0);
                break;
            case -1:
                draw_pawn(x * 100, y * 100, 0);
                draw_pawn_outline(x * 100, y * 100, 1);
                break;
            case -2:
                draw_castle(x * 100, y * 100, 0);
                draw_castle_outline(x * 100, y * 100, 1);
                break;
            case -3:
                draw_horse(x * 100, y * 100, 0);
                draw_horse_outline(x * 100, y * 100, 1);
                break;
            case -4:
                draw_bishop(x * 100, y * 100, 0);
                draw_bishop_outline(x * 100, y * 100, 1);
                break;
            case -5:
                draw_queen(x * 100, y * 100, 0);
                draw_queen_outline(x * 100, y * 100, 1);
                break;
            case -6:
                draw_king(x * 100, y * 100, 0);
                draw_king_outline(x * 100, y * 100, 1);
                break;
            }
        }
    }
}

/*void output(int x, int y, float r, float g, float b, int font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
  }*/

void  drawTurn(int x, int y)
{
    glColor3f(0, 0, 0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_LINE_STRIP); // P                //draw solid polygon
    glVertex2i(x, y);
    glVertex2i(x, y + 90);
    glVertex2i(x + 20, y + 70);
    glVertex2i(x, y + 50);//top
    glEnd();

    glBegin(GL_LINE_STRIP); //L                //draw solid polygon
    glVertex2i(x + 30, y + 90);
    glVertex2i(x + 30, y);
    glVertex2i(x + 60, y);
    glEnd();

    glBegin(GL_LINE_STRIP);//A                //draw solid polygon
    glVertex2i(x + 70, y);
    glVertex2i(x + 85, y + 90);
    glVertex2i(x + 100, y);
    glVertex2i(x + 90, y + 45);
    glVertex2i(x + 80, y + 45);
    glEnd();

    glBegin(GL_LINE_STRIP);//Y                //draw solid polygon
    glVertex2i(x + 110, y + 90);
    glVertex2i(x + 120, y + 45);
    glVertex2i(x + 120, y);
    glVertex2i(x + 120, y + 45);
    glVertex2i(x + 130, y + 90);
    glEnd();

    glBegin(GL_LINE_STRIP);//E                //draw solid polygon
    glVertex2i(x + 140, y);
    glVertex2i(x + 160, y);
    glVertex2i(x + 140, y);
    glVertex2i(x + 140, y + 45);
    glVertex2i(x + 160, y + 45);
    glVertex2i(x + 140, y + 45);
    glVertex2i(x + 140, y + 90);
    glVertex2i(x + 160, y + 90);
    glEnd();

    glBegin(GL_LINE_STRIP);//R                //draw solid polygon
    glVertex2i(x + 170, y);
    glVertex2i(x + 170, y + 90);
    glVertex2i(x + 190, y + 70);
    glVertex2i(x + 170, y + 50);
    glVertex2i(x + 190, y);
    glEnd();

    glBegin(GL_LINE_STRIP);//T                //draw solid polygon
    glVertex2i(x + 310, y + 90);
    glVertex2i(x + 340, y + 90);
    glVertex2i(x + 325, y + 90);
    glVertex2i(x + 325, y);
    glEnd();

    glBegin(GL_LINE_STRIP);//U               //draw solid polygon
    glVertex2i(x + 350, y + 90);
    glVertex2i(x + 350, y);
    glVertex2i(x + 370, y);
    glVertex2i(x + 370, y + 90);
    glEnd();

    glBegin(GL_LINE_STRIP);//R               //draw solid polygon
    glVertex2i(x + 380, y);
    glVertex2i(x + 380, y + 90);
    glVertex2i(x + 400, y + 70);
    glVertex2i(x + 380, y + 50);
    glVertex2i(x + 400, y);
    glEnd();

    glBegin(GL_LINE_STRIP);//N                //draw solid polygon
    glVertex2i(x + 410, y);
    glVertex2i(x + 410, y + 90);
    glVertex2i(x + 430, y);
    glVertex2i(x + 430, y + 90);
    glEnd();

    glFlush();

}
void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT );
  glColor3f( 0, 0, 0 );
  glPolygonMode( GL_FRONT, GL_FILL );
  bool black = true;	
  for(int y = 0; y < 800; y = y + 100){//checker pattern
    if (y %200 == 0){
      black = true;
    }else{
      black = false;
      
    }
    
    for (int x = 0; x < 800; x = x + 100)
    {
        if(black)
        {
            glColor3f( 0.0, 0, 0.4 );
	        glRecti( x,y, x+100, y+100 );//blue
	        black = false;
	        continue;
	    }
        else
	    {
	        glColor3f( 0.7, 0.1, 0.0 );
	        glRecti( x,y, x+100, y+100 );//red
	        black = true;
	        continue;
	    }
    }
  }
  glFlush();
  place_piece();
}




bool checkRule(int piece, int x, int y, int nextx, int nexty)// add player for checking turns 
{

  
  
  //reminder white is on top of the array
  if (whitesTurn){//whites turn
    if(piece < 0){
      return false;
    }
    switch(piece){///depening on peice it sees if the location 
    case 1://paws
       
     
	
      if( y+1 == nexty){
	  
	    
	    if(x == nextx){
	        if(chess_array[nexty][nextx] == 0){
                
                return true;
                
	        }
           
	        return false;
            
	    }
        else if (x - 1 == nextx) {
            if (chess_array[nexty][nextx] < 0) {
                
                return true;
            }
            
            return false;
        }
	    else if(x+1== nextx){
	        if(chess_array[nexty][nextx] < 0){
                
	            return true;
	        }
            
	        return false;
	    }	        
      }
      else if (y+2 == nexty) 
      {
          if (y == 1) 
          {
              return true;
          }
      }
      return false;
	  
	
    case 2://castle

        if (nexty > y)// checks up
        {
            for (int i = y+1; i < nexty; i++) 
            {
                if(chess_array[i][x] != 0)
                {
                    
                    return false;
                }
                
            }
            if (chess_array[nexty][x] <= 0 ) 
            {
                
                return true;
            }
            
            return false;
        }
        else if (nexty < y && x == nextx) // checks down
        {
            for (int i = y-1; i > nexty; i--)
            {
                if (chess_array[i][x] != 0)
                {
                    return false;
                }

            }
            if (chess_array[nexty][x] <= 0)
            {
                return true;
            }
            return false;
        }
        else if (nextx > x && y == nexty) // checks right
        {
            for (int i = x+1; i < nextx; i++)
            {
                if (chess_array[y][i] != 0)
                {
                    return false;
                }

            }
            if (chess_array[y][nextx] <= 0)
            {
                return true;
            }
            return false;
        }
        else if (nextx < x && y == nexty) // checks left
        {
            for (int i = x-1; i > nextx; i--)
            {
                if (chess_array[y][i] != 0)
                {
                    return false;
                }

            }
            if (chess_array[y][nextx] <= 0)
            {
                return true;
            }
            return false;
        }
      return false;

    case 3://hors
        if (nexty == (y+2))// checks up
        {
            if (nextx == (x-1)|| nextx == (x + 1))
            {
                if (chess_array[nexty][nextx] <= 0) {

                    return true;
                }
            }
            return false;
          
        }
        else if (nexty == (y + 1))// checks up
        {
            if (nextx == (x - 2) || nextx == (x + 2))
            {
                if (chess_array[nexty][nextx] <= 0) {

                    return true;
                }
            }
            return false;
        }
        else if (nexty == (y - 1))// checks up
        {
            if (nextx == (x - 2) || nextx == (x + 2))
            {
                if (chess_array[nexty][nextx] <= 0) {

                    return true;
                }
            }
            return false;
        }
        else if (nexty == (y - 2))// checks up
        {
            if (nextx == (x - 1) || nextx == (x + 1))
            {
                if (chess_array[nexty][nextx] <= 0) {

                    return true;
                }
            }
            return false;
        }
      return false;
    case 4://bishop
        int deltaY;
        int deltaX;
        if (nextx == x or nexty == y or chess_array[nexty][nextx] > 0) {
            return false;
        }
        else {
            deltaY = (nexty - y);
            deltaX = (nextx - x);
            if (abs(deltaX / deltaY) != 1) {
                return false;
            }
        }
        if (deltaY > 0) {

            

            if(deltaX > 0) {
                int i2 = y + 1;
                for (int i = x + 1; i < nextx; i++)//moving up right
                {
                    if (chess_array[i2][i] != 0)
                    {
                        
                        return false;
                    }
                    i2 = i2 + 1;
                }
               
                return true;
            }
            else {
                int i2 = y + 1;
                for (int i = x - 1; i > nextx; i--)//moving up left deltay = pos, deltax = neg 
                {
                    
                    if (chess_array[i2][i] != 0)
                    {
                        
                        return false;
                    }
                    i2 = i2 + 1;
                }
                
                return true;
            }

        }
        else {
            if (deltaX > 0) {
                int i2 = y - 1;
                for (int i = x + 1; i < nextx; i++)//moving up left deltay = neg, deltax = pos 
                {
                    if (chess_array[i2][i] != 0)
                    {
                       
                        return false;
                    }
                    i2 = i2 - 1;
                }
                
                return true;
            }
            else {
                int i2 = y - 1;
                for (int i = x - 1; i > nextx; i--)//moving down left
                {
                    if (chess_array[i2][i] != 0)
                    {
                        
                        return false;
                        
                    }
                    i2 = i2 - 1;
                }
                
                return true;

            }


        }
        return false;
    case 5://queen
        deltaX = nextx - x;
        deltaY = nexty - y;
        
        if (chess_array[nexty][nextx] > 0) {
            return false;
        }
        if (deltaX == 0 or deltaY == 0)
        {//use castle code
            if (nexty > y && x == nextx)// checks up
            {
                for (int i = y + 1; i < nexty; i++)
                {
                    if (chess_array[i][x] != 0)
                    {
                        
                        return false;
                    }

                }
                if (chess_array[nexty][x] <= 0)
                {
                    return true;
                }
                return false;
            }
            else if (nexty < y&& x == nextx) // checks down
            {
                for (int i = y - 1; i > nexty; i--)
                {
                    if (chess_array[i][x] != 0)
                    {
                        return false;
                    }

                }
                if (chess_array[nexty][x] <= 0)
                {
                    return true;

                }
                return false;
            }
            else if (nextx > x && y == nexty) // checks right
            {
                for (int i = x + 1; i < nextx; i++)
                {
                    if (chess_array[y][i] != 0)
                    {
                        return false;
                    }

                }
                if (chess_array[y][nextx] <= 0)
                {
                    return true;
                }
                return false;
            }
            else if (nextx < x&& y == nexty) // checks left
            {
                for (int i = x - 1; i > nextx; i--)
                {
                    if (chess_array[y][i] != 0)
                    {
                        return false;
                    }

                }
                if (chess_array[y][nextx] <= 0)
                {
                    return true;
                }
                return false;
            }
            return false;
        }
        else if (abs(deltaX) == abs(deltaY))
        {//use bishop code

            if (deltaY > 0) {



                if (deltaX > 0) {
                    int i2 = y + 1;
                    for (int i = x + 1; i < nextx; i++)//moving up right
                    {
                        if (chess_array[i2][i] != 0)
                        {
                            return false;
                        }
                        i2 = i2 + 1;

                    }
                    return true;
                }
                else {
                    int i2 = y + 1;
                    for (int i = x - 1; i > nextx; i--)//moving up left deltay = pos, deltax = neg 
                    {
                        if (chess_array[i2][i] != 0)
                        {
                            return false;
                        }
                        i2 = i2 + 1;
                    }
                    return true;
                }

            }
            else {
                if (deltaX > 0) {
                    int i2 = y - 1;
                    for (int i = x + 1; i < nextx; i++)//moving up left deltay = neg, deltax = pos 
                    {
                        if (chess_array[i2][i] != 0)
                        {
                            return false;
                        }
                        i2 = i2 - 1;
                    }
                    return true;
                }
                else {
                    int i2 = y - 1;
                    for (int i = x - 1; i > nextx; i--)//moving down left
                    {
                        if (chess_array[i2][i] != 0)
                        {
                         
                            return false;
                        }
                        i2 = i2 - 1;
                    }
                    return true;

                }


            }
            return false;

        }
        return false;
    case 6://king
        
        deltaX = nextx - x;
        deltaY = nexty - y;
       
        if (abs(deltaX) > 1 or abs(deltaY) > 1) {
            
            return false;
        }
        if (chess_array[nexty][nextx] > 0) {
            
            return false;
        }

      return true;
    default:
      return false;
    }
  }else{//
    if(piece > 0){
      return false;
    }
    switch(piece){//blacks turn
    case -1://pawn
      if( y-1 == nexty)
      {
	  
	    if(x-1 == nextx)
        {
	        if(chess_array[nexty][nextx] > 0)
            {
                
	            return true;
	        }
    
            return false;
	    }
	    else if(x == nextx)
        {
	        if(chess_array[nexty][nextx] == 0){
                
	            return true;
	        }
            
            return false;
	    }
	    else if(x+1== nextx){
	        if(chess_array[nexty][nextx] > 0){
                
	            return true;
	        }
            
            return false;
	    }	        
      }

      else if (y - 2 == nexty)
      {
          if (y == 6)
          {
              return true;
          }
      }
      return false;
    case -2://castle
        if (nexty > y && x == nextx)// checks up
        {
            for (int i = y+1; i < nexty; i++)
            {
                if (chess_array[i][x] != 0)
                {
                    
                    return false;
                }

            }
            if (chess_array[nexty][x] >= 0)
            {
                
                return true;
            }
            
            return false;
        }
        else if (nexty < y&& x == nextx) // checks down
        {
            for (int i = y-1; i > nexty; i--)
            {
                if (chess_array[i][x] != 0)
                {
                    
                    return false;
                }

            }
            if (chess_array[nexty][x] >= 0)
            {
                
                return true;

            }
            
            return false;
        }
        else if (nextx > x && y == nexty) // checks right
        {
            for (int i = x+1; i < nextx; i++)
            {
                if (chess_array[y][i] != 0)
                {
                    return false;
                }

            }
            if (chess_array[y][nextx] >= 0)
            {
                
                return true;
            }
            
            return false;
        }
        else if (nextx < x&& y == nexty) // checks left
        {
            for (int i = x-1; i > nextx; i--)
            {
                if (chess_array[y][i] != 0)
                {
                    
                    return false;
                }

            }
            if (chess_array[y][nextx] >= 0)
            {
                
                return true;
            }
            
            return false;
        }
      return false;
    case -3://hors
        if (nexty == (y + 2))// checks up
        {
            if (nextx == (x - 1) || nextx == (x + 1))
            {
                if (chess_array[nexty][nextx] >= 0) {

                    return true;
                }
            }
            return false;

        }
        else if (nexty == (y + 1))// checks up
        {
            if (nextx == (x - 2) || nextx == (x + 2))
            {
                if (chess_array[nexty][nextx] >= 0) {

                    return true;
                }
            }
            return false;
        }
        else if (nexty == (y - 1))// checks up
        {
            if (nextx == (x - 2) || nextx == (x + 2))
            {
                if (chess_array[nexty][nextx] >= 0) {

                    return true;
                }
            }
            return false;
        }
        else if (nexty == (y - 2))// checks up
        {
            if (nextx == (x - 1) || nextx == (x + 1))
            {
                if (chess_array[nexty][nextx] >= 0) {

                    return true;
                }
            }
            return false;
        }
      return false;
    case -4://bishop
        //int slope;
        
        if (nextx == x or nexty == y or chess_array[nexty][nextx] < 0) {
            return false;
            
        }
        
        else {
            deltaY = (nexty - y);
            deltaX = (nextx - x);
            //slope = deltaY/deltaX;
            if (abs(deltaX / deltaY) != 1)
                return false;
        }
        if (deltaY > 0) {



            if (deltaX > 0) {
                int i2 = y + 1;
                for (int i = x + 1; i < nextx; i++)//moving up right
                {
                    if (chess_array[i2][i] != 0)
                    {
                       
                        return false;
                    }
                    i2 = i2 + 1;

                }
                return true;
            }
            else {
                int i2 = y + 1;
                for (int i = x - 1; i > nextx ; i--)//moving up left deltay = pos, deltax = neg 
                {
                    if (chess_array[i2][i] != 0)
                    {
                        
                        return false;
                    }
                    i2 = i2 + 1;
                }
                return true;
            }
            
        }
        else {
            if (deltaX > 0) {
                int i2 = y - 1;
                for (int i = x + 1; i < nextx; i++)//moving up left deltay = neg, deltax = pos 
                {
                    if (chess_array[i2][i] != 0)
                    {
                        
                        return false;
                    }
                    i2 = i2 - 1;
                }
                return true;
            }
            else {
                int i2 = y - 1;
                for (int i = x - 1; i > nextx; i--)//moving down left
                {
                    if (chess_array[i2][i] != 0)
                    {
                        
                        return false;
                    }
                    i2 = i2 - 1;
                }
                return true;

            }

        
        }
      return false;
    case -5://queen
        deltaX = nextx - x;
        deltaY = nexty - y;
        
        if (chess_array[nexty][nextx] < 0) {
            return false;
        }
        if (deltaX == 0 or deltaY == 0)
        {//use castle code
            if (nexty > y && x == nextx)// checks up
            {
                for (int i = y + 1; i < nexty; i++)
                {
                    if (chess_array[i][x] != 0)
                    {
                        
                        return false;
                    }

                }
                if (chess_array[nexty][x] >= 0)
                {
                    
                    return true;
                }
                
                return false;
            }
            else if (nexty < y&& x == nextx) // checks down
            {
                for (int i = y - 1; i > nexty; i--)
                {
                    if (chess_array[i][x] != 0)
                    {
                        
                        return false;
                    }

                }
                if (chess_array[nexty][x] >= 0)
                {
                    
                    return true;

                }
                
                return false;
            }
            else if (nextx > x && y == nexty) // checks right
            {
                for (int i = x + 1; i < nextx; i++)
                {
                    if (chess_array[y][i] != 0)
                    {
                        
                        return false;
                    }

                }
                if (chess_array[y][nextx] >= 0)
                {
                    
                    return true;
                }
                
                return false;
            }
            else if (nextx < x&& y == nexty) // checks left
            {
                for (int i = x - 1; i > nextx; i--)
                {
                    
                    if (chess_array[y][i] != 0)
                    {
                       
                        return false;
                    }

                }
                if (chess_array[y][nextx] >= 0)
                {
                    
                    return true;
                }
                
                return false;
            }
            return false;
        }
        else if(abs(deltaX) == abs(deltaY))
        {//use bishop code
            
            if (deltaY > 0) {



                if (deltaX > 0) {
                    int i2 = y + 1;
                    for (int i = x + 1; i < nextx; i++)//moving up right
                    {
                        if (chess_array[i2][i] != 0)
                        {
                            return false;
                        }
                        i2 = i2 + 1;

                    }
                    return true;
                }
                else {
                    int i2 = y + 1;
                    for (int i = x - 1; i > nextx; i--)//moving up left deltay = pos, deltax = neg 
                    {
                        if (chess_array[i2][i] != 0)
                        {
                            
                            return false;
                        }
                        i2 = i2 + 1;
                    }
                    return true;
                }

            }
            else {
                if (deltaX > 0) {
                    int i2 = y - 1;
                    for (int i = x + 1; i < nextx; i++)//moving up left deltay = neg, deltax = pos 
                    {
                        if (chess_array[i2][i] != 0)
                        {
                            
                            return false;
                        }
                        i2 = i2 - 1;
                    }
                    return true;
                }
                else {
                    int i2 = y - 1;
                    for (int i = x - 1; i > nextx; i--)//moving down left
                    {
                        if (chess_array[i2][i] != 0)
                        {
                           
                            return false;
                        }
                        i2 = i2 - 1;
                    }
                    return true;

                }


            }
            return false;
        
        }
      return false;
    case -6://king
        deltaX = nextx - x;
        deltaY = nexty - y;
        if (abs(deltaX) > 1 or abs(deltaY) > 1) {
            return false;
        }
        if (chess_array[nexty][nextx] < 0) {
            return false;
        }

      return true;
    default:
      return false;
    }
    return false;
  }
}

void checkpiece(int x, int y)
{
  if(lastPiece != 0)
    {
      if(checkRule(lastPiece,lastx,lasty,std::floor(x/100), std::floor(y / 100)))
      {
          
	    chess_array[lasty][lastx] = 0;
	    lasty = std::floor(y / 100);
	    lastx = std::floor(x/100);
      
	    chess_array[lasty][lastx] = lastPiece;
	    lastPiece = 0;
	    whitesTurn = !whitesTurn;
        display();
      }
      
	  lasty = std::floor(y / 100);//set last click to current piece
	  lastx = std::floor(x/100);
      
      
	  lastPiece = 0;
      
    }
  else
    {
      lasty = std::floor(y / 100);
      lastx = std::floor(x/100);
      
      lastPiece = chess_array[lasty][lastx];
      

      
    }
  //call higlight if peice is selected
  

}
void drawDot( int x, int y )
{
  glBegin( GL_POINTS );			
    glVertex2i(x - xoffset, screenHeight - y);
    
  glEnd();
} //drawDot

void myMouse( int button, int state, int x, int y )
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        
        checkpiece(x - xoffset, screenHeight - y);
    }

  glFlush();				//send all output to screen
}

void myMovedMouse(  int mouseX, int mouseY)
{
  GLint x = mouseX - xoffset;
  GLint y = screenHeight - mouseY;
  GLint brushsize = 2;
  
  glRecti ( x, y, x + brushsize, y + brushsize );
  glFlush();
} //myMovedMouse

void myKeyboard ( unsigned char key, int mouseX, int mouseY )
{
  GLint x = mouseX - xoffset;
  GLint y = screenHeight - mouseY;
  switch( key )
    {
    case 'p':
      drawDot ( x, y );
      break;
    case 'e':
      exit ( -1 );
    default :
      break;
    case 'b':
      glColor3f( 0.0, 0.0, 1.0 );
      break;
    case 'r':
      glColor3f( 1.0, 0.0, 0.0 );
      break;
    case 'g':
      glColor3f( 0.0, 1.0, 0.0 );
      break;
    }  
}
