/*
**  File with Constants used in different computations  
*/

# ifndef _CONST_H_
# define _CONST_H_

static const int Ap_coord[40][8] = 
{
  {0, 0, 0, 0, 0, 0, 0, 0},      //1
  {1, 6, 18, 0, 0, 0, 0, 0},     //2
  {1, 6, 22, 0, 0, 0, 0, 0},     //3
  {1, 6, 26, 0, 0, 0, 0, 0},     //4
  {1, 6, 30, 0, 0, 0, 0, 0},     //5
  {1, 6, 34, 0, 0, 0, 0, 0},     //6
  {6, 6, 22, 38, 0, 0, 0, 0},     //7
  {6, 6, 24, 42, 0, 0, 0, 0},     //8
  {6, 6, 26, 46, 0, 0, 0, 0},     //9
  {6, 6, 28, 50, 0, 0, 0, 0},     //10
  {6, 6, 30, 54, 0, 0, 0, 0},     //11
  {6, 6, 32, 58, 0, 0, 0, 0},     //12
  {6, 6, 34, 62, 0, 0, 0, 0},     //13
  {13, 6, 26, 46, 66, 0, 0, 0},    //14
  {13, 6, 26, 48, 70, 0, 0, 0},    //15
  {13, 6, 26, 50, 74, 0, 0, 0},    //16
  {13, 6, 30, 54, 78, 0, 0, 0},    //17
  {13, 6, 30, 56, 82, 0, 0, 0},    //18
  {13, 6, 30, 58, 86, 0, 0, 0},    //19    
  {13, 6, 34, 62, 90, 0, 0, 0},    //20
  {22, 6, 28, 50, 72, 94, 0, 0},    //21
  {22, 6, 26, 50, 74, 98, 0, 0},    //22
  {22, 6, 30, 54, 78, 102, 0, 0},    //23
  {22, 6, 28, 54, 80, 106, 0, 0},    //24
  {22, 6, 32, 58, 84, 110, 0, 0},    //25
  {22, 6, 30, 58, 86, 114, 0, 0},    //26
  {22, 6, 34, 62, 90, 118, 0, 0},    //27
  {33, 6, 26, 50, 74, 98, 122, 0},    //28
  {33, 6, 30, 54, 78, 102, 126, 0},    //29
  {33, 6, 26, 52, 78, 104, 130, 0},    //30
  {33, 6, 30, 56, 82, 108, 134, 0},    //31
  {33, 6, 34, 60, 86, 112, 138, 0},    //32
  {33, 6, 30, 58, 86, 114, 142, 0},    //33
  {33, 6, 34, 63, 90, 118, 146, 0},    //34
  {46, 6, 30, 54, 78, 102, 126, 150},    //35
  {46, 6, 24, 50, 76, 102, 128, 154},    //36
  {46, 6, 28, 54, 80, 106, 132, 158},    //37
  {46, 6, 32, 58, 84, 110, 136, 162},    //38
  {46, 6, 26, 54, 82, 110, 138, 166},    //39
  {46, 6, 30, 58, 86, 114, 142, 170}    //40
}; 

static const char V_bits[34][18] =
{
    "000111110010010100",   //7
    "001000010110111100",   //8
    "001001101010011001",   //9
    "001010010011010011",   //10
    "001011101111110110",   //11
    "001100011101100010",   //12
    "001101100001000111",   //13
    "001110011000001101",  //14
    "001111100100101000",  //15
    "010000101101111000",  //16
    "010001010001011101",  //17
    "010010101000010111",  //18
    "010011010100110010",  //19
    "010100100110100110",  //20
    "010101011010000011",  //21
    "010110100011001001",  //22
    "010111011111101100",  //23
    "011000111011000100",  //24
    "011001000111100001",  //25
    "011010111110101011",  //26
    "011011000010001110",  //27
    "011100110000011010",  //28
    "011101001100111111",  //29
    "011110110101110101",  //30
    "011111001001010000",  //31
    "100000100111010101",  //32
    "100001011011110000",  //33
    "100010100010111010",  //34
    "100011011110011111",  //35
    "100101010000101110",  //36
    "100101010000101110",  //37
    "100110101001100100",  //38
    "100111010101000001",  //39
    "101000110001101001"   //40  
};

# endif
