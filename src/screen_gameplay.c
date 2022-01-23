/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include <string.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
char word[] = "WORDS";
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int wordSpacing = 100;
int wordSize = 0;
Vector2 * letterPositions;
int letterButtonYOffset = 85;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------
void DrawWord();
void setLetterPositions();
int ClickCollides(int minX, int minY, int maxX, int maxY);
void IncrementLetter(int index);
void DecrementLetter(int index);
int GetLetterIndex(char letter);

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    setLetterPositions();
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsMouseButtonReleased(0))// removed: IsGestureDetected(GESTURE_TAP) ||
    {
      for(int i=0;i<wordSize;i++){
        if(ClickCollides(
          letterPositions[i].x-fontLarge.baseSize/5,
          letterPositions[i].y-letterButtonYOffset-10-fontLarge.baseSize/5,
          letterPositions[i].x+fontLarge.baseSize/5,
          letterPositions[i].y-letterButtonYOffset-10+fontLarge.baseSize/5
        ) == 1){
          IncrementLetter(i);
        }else if(ClickCollides(
          letterPositions[i].x-fontLarge.baseSize/5,
          letterPositions[i].y+letterButtonYOffset-5-fontLarge.baseSize/5,
          letterPositions[i].x+fontLarge.baseSize/5,
          letterPositions[i].y+letterButtonYOffset-5+fontLarge.baseSize/5
        ) == 1){
          DecrementLetter(i);
        }
      }
    }
}

void IncrementLetter(int index){
  if(word[index]=='Z'){
    word[index]='A';
  }else{
    word[index]=alphabet[GetLetterIndex(word[index])+1];
  }
}

void DecrementLetter(int index){
  if(word[index]=='A'){
    word[index]='Z';
  }else{
    word[index]=alphabet[GetLetterIndex(word[index])-1];
  }
}

int GetLetterIndex(char letter){
  for(int i = 0;i<26;i++){
    if(alphabet[i]==letter){
      return i;
    }
  }
  return -1;
}

int ClickCollides(int minX, int minY, int maxX, int maxY){
  Vector2 clickPosition = GetMousePosition();
  if(clickPosition.x>minX){
    if(clickPosition.x<maxX){
      if(clickPosition.y>minY){
        if(clickPosition.y<maxY){
          return 1;
        }
      }
    }
  }
  return 0;
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BEIGE);
    DrawWord();

}

void DrawWord(){
  for(int i=0;i<wordSize;i++){
    char curLetter = word[i];
    Vector2 letterSize = MeasureTextEx(fontLarge,&curLetter,fontLarge.baseSize,0);
    DrawTextEx(fontLarge,&curLetter,(Vector2){letterPositions[i].x-letterSize.x/2,letterPositions[i].y-letterSize.y/2},fontLarge.baseSize,0,BLACK);
    DrawTriangle(
      (Vector2){letterPositions[i].x,letterPositions[i].y-letterButtonYOffset-10-fontLarge.baseSize/5},
      (Vector2){letterPositions[i].x-fontLarge.baseSize/5,letterPositions[i].y-letterButtonYOffset-10+fontLarge.baseSize/5},
      (Vector2){letterPositions[i].x+fontLarge.baseSize/5,letterPositions[i].y-letterButtonYOffset-10+fontLarge.baseSize/5}, BLACK);
    DrawTriangle(
      (Vector2){letterPositions[i].x,letterPositions[i].y+letterButtonYOffset-5+fontLarge.baseSize/5},
      (Vector2){letterPositions[i].x+fontLarge.baseSize/5,letterPositions[i].y+letterButtonYOffset-5-fontLarge.baseSize/5},
      (Vector2){letterPositions[i].x-fontLarge.baseSize/5,letterPositions[i].y+letterButtonYOffset-5-fontLarge.baseSize/5},
      BLACK);
  }
}

void setLetterPositions(){
  wordSize = strlen(word);
  letterPositions = (Vector2 *) malloc(wordSize * sizeof(Vector2));
  int wordSpaceWidth = wordSpacing * (wordSize-1);
  int startingPoint = GetScreenWidth()/2 - wordSpaceWidth/2;
  for(int i=0;i<wordSize;i++){
    letterPositions[i].y=GetScreenHeight()/2;
    letterPositions[i].x = startingPoint + wordSpacing * i;
  }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    free(letterPositions);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
