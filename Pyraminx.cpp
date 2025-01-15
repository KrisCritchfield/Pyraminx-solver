#include "Pyraminx.h"

    pyraminx::pyraminx()
    {
        for(int i = 0; i<16; i++)
        {
            redside.push_back('R');       //front side
            greenside.push_back('G');     //left side
            yellowside.push_back('Y');    //yellow side
            blueside.push_back('b');      //bottom side
        }
    }

    pyraminx::pyraminx(const pyraminx& other)
        : redside(other.redside),
          greenside(other.greenside),
          yellowside(other.yellowside),
          blueside(other.blueside) {}


//for my implmentation I decided to make each face its own 1D array and number each sticker
//and then manually implement each turn with array switching. Below is a representation of how I numbered
//each face and their colors R=red, G=green Y=yellow and b=blue
//
//             G0                            R0                           Y0
//         G1  G2  G3                    R1  R2  R3                   Y1  Y2  Y3
//     G4  G5  G6  G7  G8            R4  R5  R6  R7  R8           Y4  Y5  Y6  Y7  Y8
//  G9 G10 G11 G12 G13 G14 G15    R9 R10 R11 R12 R13 R14 R15   Y9 Y10 Y11 Y12 Y13 Y14 Y15
//               
//                                b15 b14 b13 b12 b11 b10 b9
//                                    b8  b7  b6  b5  b4
//                                        b3  b2  b1 
//                                            b0
//
//this will help visualize and verify they are all legal moves, I chose to print it this way simply because its
//the easiest way fro me to visualize it
//

    void pyraminx::rotateface(std::vector<char>& face, int clockwise)
    {
        std::vector<char> copy;
        for(int i=0; i<16; i++)
        {
            copy.push_back(face[i]);
        }
        if(clockwise)
        {
            face[0] = copy[9];
            face[1] = copy[11];
            face[2] = copy[10];
            face[3] = copy[4];
            face[4] = copy[13];
            face[5] = copy[12];
            face[6] = copy[6];
            face[7] = copy[5];
            face[8] = copy[1];
            face[9] = copy[15];
            face[10] = copy[14];
            face[11] = copy[8];
            face[12] = copy[7];
            face[13] = copy[3];
            face[14] = copy[2];
            face[15] = copy[0];
        }
        else
        {
            face[0] = copy[15];
            face[1] = copy[8];
            face[2] = copy[14];
            face[3] = copy[13];
            face[4] = copy[3];
            face[5] = copy[7];
            face[6] = copy[6];
            face[7] = copy[12];
            face[8] = copy[11];
            face[9] = copy[0];
            face[10] = copy[2];
            face[11] = copy[1];
            face[12] = copy[5];
            face[13] = copy[4];
            face[14] = copy[10];
            face[15] = copy[9];
        }
    }


//this starts as the red, green, yellow corner (rotate blue face on row 3)
    void pyraminx::topcornercounter()
    {
        char placeholder = redside[0];
        redside[0] = greenside[0];
        greenside[0] = yellowside[0];
        yellowside[0] = placeholder;
    }

    void pyraminx::topcorner()
    {
        char placeholder = redside[0];
        redside[0] = yellowside[0];
        yellowside[0] = greenside[0];
        greenside[0] = placeholder;
    }

    void pyraminx::toprow1counter()
    {
        std::vector<char> placeholder;
        for(int i=1; i<4; i++)
        {
            placeholder.push_back(redside[i]);
            redside[i]=greenside[i];
            greenside[i]=yellowside[i];
            yellowside[i]= placeholder[i-1];
        }
    }

    void pyraminx::toprow1()
    {
        std::vector<char> placeholder;
        for(int i=1; i<4; i++)
        {
            placeholder.push_back(redside[i]);
            redside[i]=yellowside[i];
            yellowside[i]=greenside[i];
            greenside[i]= placeholder[i-1];
        }
    }

    void pyraminx::toprow2counter()
    {
        std::vector<char> placeholder;
        for(int i=4; i<9; i++)
        {
            placeholder.push_back(redside[i]);
            redside[i]=greenside[i];
            greenside[i]=yellowside[i];
            yellowside[i]= placeholder[i-4];
        }
    }

    void pyraminx::toprow2()
    {
        std::vector<char> placeholder;
        for(int i=4; i<9; i++)
        {
            placeholder.push_back(redside[i]);
            redside[i]=yellowside[i];
            yellowside[i]=greenside[i];
            greenside[i]= placeholder[i-4];
        }
    }

    void pyraminx::toprow3counter()
    {
        std::vector<char> placeholder;
        for(int i=9; i<16; i++)
        {
            placeholder.push_back(redside[i]);
            redside[i]=greenside[i];
            greenside[i]=yellowside[i];
            yellowside[i]= placeholder[i-9];
        }
        rotateface(blueside, 1);
    }

    void pyraminx::toprow3()
    {
        std::vector<char> placeholder;
        for(int i=9; i<16; i++)
        {
            placeholder.push_back(redside[i]);
            redside[i]=yellowside[i];
            yellowside[i]=greenside[i];
            greenside[i]= placeholder[i-9];
        }

        rotateface(blueside, 0);
    }

    void pyraminx::topcornercounterplus(int k)
    {
        switch(k)
        {
            case 1:
            topcornercounter();
            break;

            case 2:
            topcornercounter();
            toprow1counter();
            break;

            case 3:
            topcornercounter();
            toprow1counter();
            toprow2counter();
            break;
        }
    }

    void pyraminx::topcornerplus(int k)
    {
        switch(k)
        {
            case 1:
            topcorner();
            break;

            case 2:
            topcorner();
            toprow1();
            break;

            case 3:
            topcorner();
            toprow1();
            toprow2();
            break;
        }
    }




//this starts as the red, green, blue corner (rotate yellow face on row 3)

    void pyraminx::leftcornercounter()
    {
        char placeholder = redside[9];
        redside[9] = blueside[15];
        blueside[15] = greenside[15];
        greenside[15] = placeholder;
    }

    void pyraminx::leftcorner()
    {
        char placeholder = redside[9];
        redside[9] = greenside[15];
        greenside[15] = blueside[15];
        blueside[15] = placeholder;
    }

    void pyraminx::leftrow1counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[11]);
        placeholder.push_back(redside[10]);
        placeholder.push_back(redside[4]);
        redside[4] = blueside[13];
        redside[10] = blueside[14];
        redside[11] = blueside[8];

        blueside[13] = greenside[13];
        blueside[14] = greenside[14];
        blueside[8] = greenside[8];

        greenside[13] = placeholder[2];
        greenside[14] = placeholder[1];
        greenside[8] = placeholder[0];
    }

    void pyraminx::leftrow1()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[11]);
        placeholder.push_back(redside[10]);
        placeholder.push_back(redside[4]);
        redside[4] = greenside[13];
        redside[10] = greenside[14];
        redside[11] = greenside[8];
        greenside[13] = blueside[13];
        greenside[14] = blueside[14];
        greenside[8] = blueside[8];
        blueside[13] = placeholder[2];
        blueside[14] = placeholder[1];
        blueside[8] = placeholder[0];
    }

    void pyraminx::leftrow2counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[1]);
        placeholder.push_back(redside[5]);
        placeholder.push_back(redside[6]);
        placeholder.push_back(redside[12]);
        placeholder.push_back(redside[13]);
        redside[13] = blueside[3];
        redside[12] = blueside[7];
        redside[6] = blueside[6];
        redside[5] = blueside[12];
        redside[1] = blueside[11];

        blueside[3] = greenside[3];
        blueside[7] = greenside[7];
        blueside[6] = greenside[6];
        blueside[12] = greenside[12];
        blueside[11] = greenside[11];

        greenside[11] = placeholder[0];
        greenside[12] = placeholder[1];
        greenside[6] = placeholder[2];
        greenside[7] = placeholder[3];
        greenside[3] = placeholder[4];
    }

    void pyraminx::leftrow2()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[1]);
        placeholder.push_back(redside[5]);
        placeholder.push_back(redside[6]);
        placeholder.push_back(redside[12]);
        placeholder.push_back(redside[13]);
        redside[13] = greenside[3];
        redside[12] = greenside[7];
        redside[6] = greenside[6];
        redside[5] = greenside[12];
        redside[1] = greenside[11];

        greenside[3] = blueside[3];
        greenside[7] = blueside[7];
        greenside[6] = blueside[6];
        greenside[12] = blueside[12];
        greenside[11] = blueside[11];

        blueside[11] = placeholder[0];
        blueside[12] = placeholder[1];
        blueside[6] = placeholder[2];
        blueside[7] = placeholder[3];
        blueside[3] = placeholder[4];
    }

    void pyraminx::leftrow3counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[0]);
        placeholder.push_back(redside[2]);
        placeholder.push_back(redside[3]);
        placeholder.push_back(redside[7]);
        placeholder.push_back(redside[8]);
        placeholder.push_back(redside[14]);
        placeholder.push_back(redside[15]);
        redside[15] = blueside[0];
        redside[14] = blueside[2];
        redside[8] = blueside[1];
        redside[7] = blueside[5];
        redside[3] = blueside[4];
        redside[2] = blueside[10];
        redside[0] = blueside[9];

        blueside[0] = greenside[0];
        blueside[1] = greenside[1];
        blueside[2] = greenside[2];
        blueside[4] = greenside[4];
        blueside[5] = greenside[5];
        blueside[9] = greenside[9];
        blueside[10] = greenside[10];

        greenside[0] = placeholder[6];
        greenside[1] = placeholder[4];
        greenside[2] = placeholder[5];
        greenside[4] = placeholder[2];
        greenside[5] = placeholder[3];
        greenside[9] = placeholder[0];
        greenside[10] = placeholder[1];

        rotateface(yellowside, 1);
    }

    void pyraminx::leftrow3()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[0]);
        placeholder.push_back(redside[2]);
        placeholder.push_back(redside[3]);
        placeholder.push_back(redside[7]);
        placeholder.push_back(redside[8]);
        placeholder.push_back(redside[14]);
        placeholder.push_back(redside[15]);
        redside[15] = greenside[0];
        redside[14] = greenside[2];
        redside[8] = greenside[1];
        redside[7] = greenside[5];
        redside[3] = greenside[4];
        redside[2] = greenside[10];
        redside[0] = greenside[9];

        greenside[0] = blueside[0];
        greenside[1] = blueside[1];
        greenside[2] = blueside[2];
        greenside[4] = blueside[4];
        greenside[5] = blueside[5];
        greenside[9] = blueside[9];
        greenside[10] = blueside[10];

        blueside[0] = placeholder[6];
        blueside[1] = placeholder[4];
        blueside[2] = placeholder[5];
        blueside[4] = placeholder[2];
        blueside[5] = placeholder[3];
        blueside[9] = placeholder[0];
        blueside[10] = placeholder[1];

        rotateface(yellowside, 0);
    }

    void pyraminx::leftcornercounterplus(int k)
    {
        switch(k)
        {
            case 1:
            leftcornercounter();
            break;

            case 2:
            leftcornercounter();
            leftrow1counter();
            break;

            case 3:
            leftcornercounter();
            leftrow1counter();
            leftrow2counter();
            break;
        }
    }

    void pyraminx::leftcornerplus(int k)
    {
        switch(k)
        {
            case 1:
            leftcorner();
            break;

            case 2:
            leftcorner();
            leftrow1();
            break;

            case 3:
            leftcorner();
            leftrow1();
            leftrow2();
            break;
        }
    }


//this starts as the red, blue, yellow corner (rotate green face on row 3)

    void pyraminx::rightcorner()
    {
        char placeholder = redside[15];
        redside[15] = blueside[9];
        blueside[9] = yellowside[9];
        yellowside[9] = placeholder;
    }

    void pyraminx::rightcornercounter()
    {
        char placeholder = redside[15];
        redside[15] = yellowside[9];
        yellowside[9] = blueside[9];
        blueside[9] = placeholder;
    }

    void pyraminx::rightrow1()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[8]);
        placeholder.push_back(redside[14]);
        placeholder.push_back(redside[13]);
        redside[8] = blueside[11];
        redside[14] = blueside[10];
        redside[13] = blueside[4];

        blueside[11] = yellowside[11];
        blueside[10] = yellowside[10];
        blueside[4] = yellowside[4];
        
        yellowside[11] = placeholder[0];
        yellowside[10] = placeholder[1];
        yellowside[4] = placeholder[2];
    }

    void pyraminx::rightrow1counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[8]);
        placeholder.push_back(redside[14]);
        placeholder.push_back(redside[13]);
        redside[8] = yellowside[11];
        redside[14] = yellowside[10];
        redside[13] = yellowside[4];

        yellowside[11] = blueside[11];
        yellowside[10] = blueside[10];
        yellowside[4] = blueside[4];
        
        blueside[11] = placeholder[0];
        blueside[10] = placeholder[1];
        blueside[4] = placeholder[2];
    }

    void pyraminx::rightrow2counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[3]);
        placeholder.push_back(redside[7]);
        placeholder.push_back(redside[6]);
        placeholder.push_back(redside[12]);
        placeholder.push_back(redside[11]);
        redside[3] = yellowside[13];
        redside[7] = yellowside[12];
        redside[6] = yellowside[6];
        redside[12] = yellowside[5];
        redside[11] = yellowside[1];

        yellowside[13] = blueside[13];
        yellowside[12] = blueside[12];
        yellowside[6] = blueside[6];
        yellowside[5] = blueside[5];
        yellowside[1] = blueside[1];

        blueside[13] = placeholder[0];
        blueside[12] = placeholder[1];
        blueside[6] = placeholder[2];
        blueside[5] = placeholder[3];
        blueside[1] = placeholder[4];
    }

    void pyraminx::rightrow2()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[3]);
        placeholder.push_back(redside[7]);
        placeholder.push_back(redside[6]);
        placeholder.push_back(redside[12]);
        placeholder.push_back(redside[11]);
        redside[3] = blueside[13];
        redside[7] = blueside[12];
        redside[6] = blueside[6];
        redside[12] = blueside[5];
        redside[11] = blueside[1];

        blueside[13] = yellowside[13];
        blueside[12] = yellowside[12];
        blueside[6] = yellowside[6];
        blueside[5] = yellowside[5];
        blueside[1] = yellowside[1];

        yellowside[13] = placeholder[0];
        yellowside[12] = placeholder[1];
        yellowside[6] = placeholder[2];
        yellowside[5] = placeholder[3];
        yellowside[1] = placeholder[4];
    }

    void pyraminx::rightrow3counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[0]);
        placeholder.push_back(redside[2]);
        placeholder.push_back(redside[1]);
        placeholder.push_back(redside[5]);
        placeholder.push_back(redside[4]);
        placeholder.push_back(redside[10]);
        placeholder.push_back(redside[9]);
        redside[0] = yellowside[15];
        redside[2] = yellowside[14];
        redside[1] = yellowside[8];
        redside[5] = yellowside[7];
        redside[4] = yellowside[3];
        redside[10] = yellowside[2];
        redside[9] = yellowside[0];

        yellowside[15] =  blueside[15];
        yellowside[14] =  blueside[14];
        yellowside[8] =  blueside[8];
        yellowside[7] =  blueside[7];
        yellowside[3] =  blueside[3];
        yellowside[2] =  blueside[2];
        yellowside[0] =  blueside[0];

         blueside[15] = placeholder[0];
         blueside[14] = placeholder[1];
         blueside[8] = placeholder[2];
         blueside[7] = placeholder[3];
         blueside[3] = placeholder[4];
         blueside[2] = placeholder[5];
         blueside[0] = placeholder[6];

         rotateface(greenside, 1);
    }

    void pyraminx::rightrow3()
    {
        std::vector<char> placeholder;
        placeholder.push_back(redside[0]);
        placeholder.push_back(redside[2]);
        placeholder.push_back(redside[1]);
        placeholder.push_back(redside[5]);
        placeholder.push_back(redside[4]);
        placeholder.push_back(redside[10]);
        placeholder.push_back(redside[9]);
        redside[0] = blueside[15];
        redside[2] = blueside[14];
        redside[1] = blueside[8];
        redside[5] = blueside[7];
        redside[4] = blueside[3];
        redside[10] = blueside[2];
        redside[9] = blueside[0];

        blueside[15] =  yellowside[15];
        blueside[14] =  yellowside[14];
        blueside[8] =  yellowside[8];
        blueside[7] =  yellowside[7];
        blueside[3] =  yellowside[3];
        blueside[2] =  yellowside[2];
        blueside[0] =  yellowside[0];

         yellowside[15] = placeholder[0];
         yellowside[14] = placeholder[1];
         yellowside[8] = placeholder[2];
         yellowside[7] = placeholder[3];
         yellowside[3] = placeholder[4];
         yellowside[2] = placeholder[5];
         yellowside[0] = placeholder[6];

         rotateface(greenside, 0);
    }

    void pyraminx::rightcornercounterplus(int k)
    {
        switch(k)
        {
            case 1:
            rightcornercounter();
            break;

            case 2:
            rightcornercounter();
            rightrow1counter();
            break;

            case 3:
            rightcornercounter();
            rightrow1counter();
            rightrow2counter();
            break;
        }
    }

    void pyraminx::rightcornerplus(int k)
    {
        switch(k)
        {
            case 1:
            rightcorner();
            break;

            case 2:
            rightcorner();
            rightrow1();
            break;

            case 3:
            rightcorner();
            rightrow1();
            rightrow2();
            break;
        }
    }


//this starts as the blue, green, yellow corner (rotate red face on row 3)

    void pyraminx::backcornercounter()
    {
        char placeholder = blueside[0];
        blueside[0] = yellowside[15];
        yellowside[15] = greenside[9];
        greenside[9] = placeholder;
    }

    void pyraminx::backcorner()
    {
        char placeholder = blueside[0];
        blueside[0] = greenside[9];
        greenside[9] = yellowside[15];
        yellowside[15] = placeholder;
    }

    void pyraminx::backrow1counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(blueside[1]);
        placeholder.push_back(blueside[2]);
        placeholder.push_back(blueside[3]);
        blueside[1] = yellowside[8];
        blueside[2] = yellowside[14];
        blueside[3] = yellowside[13];

        yellowside[13] = greenside[4];
        yellowside[14] = greenside[10];
        yellowside[8] = greenside[11];

        greenside[4] = placeholder[2];
        greenside[10] = placeholder[1];
        greenside[11] = placeholder[0];
    }

    void pyraminx::backrow1()
    {
        std::vector<char> placeholder;
        placeholder.push_back(blueside[1]);
        placeholder.push_back(blueside[2]);
        placeholder.push_back(blueside[3]);
        blueside[1] = greenside[11];
        blueside[2] = greenside[10];
        blueside[3] = greenside[4];

        greenside[4] = yellowside[13];
        greenside[10] = yellowside[14];
        greenside[11] = yellowside[8];

        yellowside[13] = placeholder[2];
        yellowside[14] = placeholder[1];
        yellowside[8] = placeholder[0];
    }

    void pyraminx::backrow2counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(blueside[4]);
        placeholder.push_back(blueside[5]);
        placeholder.push_back(blueside[6]);
        placeholder.push_back(blueside[7]);
        placeholder.push_back(blueside[8]);

        blueside[4] = yellowside[3];
        blueside[5] = yellowside[7];
        blueside[6] = yellowside[6];
        blueside[7] = yellowside[12];
        blueside[8] = yellowside[11];

        yellowside[3] = greenside[13];
        yellowside[7] = greenside[12];
        yellowside[6] = greenside[6];
        yellowside[12] = greenside[5];
        yellowside[11] = greenside[1];

        greenside[13] = placeholder[0];
        greenside[12] = placeholder[1];
        greenside[6] = placeholder[2];
        greenside[5] = placeholder[3];
        greenside[1] = placeholder[4];
    }

    void pyraminx::backrow2()
    {
        std::vector<char> placeholder;
        placeholder.push_back(blueside[4]);
        placeholder.push_back(blueside[5]);
        placeholder.push_back(blueside[6]);
        placeholder.push_back(blueside[7]);
        placeholder.push_back(blueside[8]);

        blueside[4] = greenside[13];
        blueside[5] = greenside[12];
        blueside[6] = greenside[6];
        blueside[7] = greenside[5];
        blueside[8] = greenside[1];

        greenside[13] = yellowside[3];
        greenside[12] = yellowside[7];
        greenside[6] = yellowside[6];
        greenside[5] = yellowside[12];
        greenside[1] = yellowside[11];

        yellowside[3] = placeholder[0];
        yellowside[7] = placeholder[1];
        yellowside[6] = placeholder[2];
        yellowside[12] = placeholder[3];
        yellowside[11] = placeholder[4];
    }

    void pyraminx::backrow3counter()
    {
        std::vector<char> placeholder;
        placeholder.push_back(blueside[9]);
        placeholder.push_back(blueside[10]);
        placeholder.push_back(blueside[11]);
        placeholder.push_back(blueside[12]);
        placeholder.push_back(blueside[13]);
        placeholder.push_back(blueside[14]);
        placeholder.push_back(blueside[15]);
        blueside[9] = yellowside[0];
        blueside[10] = yellowside[2];
        blueside[11] = yellowside[1];
        blueside[12] = yellowside[5];
        blueside[13] = yellowside[4];
        blueside[14] = yellowside[10];
        blueside[15] = yellowside[9];

        yellowside[0] = greenside[15];
        yellowside[2] = greenside[14];
        yellowside[1] = greenside[8];
        yellowside[5] = greenside[7];
        yellowside[4] = greenside[3];
        yellowside[10] = greenside[2];
        yellowside[9] = greenside[0];

        greenside[15] = placeholder[0];
        greenside[14] = placeholder[1];
        greenside[8] = placeholder[2];
        greenside[7] = placeholder[3];
        greenside[3] = placeholder[4];
        greenside[2] = placeholder[5];
        greenside[0] = placeholder[6];

        rotateface(redside, 1);
    }

    void pyraminx::backrow3()
    {
        std::vector<char> placeholder;
        placeholder.push_back(blueside[9]);
        placeholder.push_back(blueside[10]);
        placeholder.push_back(blueside[11]);
        placeholder.push_back(blueside[12]);
        placeholder.push_back(blueside[13]);
        placeholder.push_back(blueside[14]);
        placeholder.push_back(blueside[15]);
        blueside[9] = greenside[15];
        blueside[10] = greenside[14];
        blueside[11] = greenside[8];
        blueside[12] = greenside[7];
        blueside[13] = greenside[3];
        blueside[14] = greenside[2];
        blueside[15] = greenside[0];

        greenside[15] = yellowside[0];
        greenside[14] = yellowside[2];
        greenside[8] = yellowside[1];
        greenside[7] = yellowside[5];
        greenside[3] = yellowside[4];
        greenside[2] = yellowside[10];
        greenside[0] = yellowside[9];

        yellowside[0] = placeholder[0];
        yellowside[2] = placeholder[1];
        yellowside[1] = placeholder[2];
        yellowside[5] = placeholder[3];
        yellowside[4] = placeholder[4];
        yellowside[10] = placeholder[5];
        yellowside[9] = placeholder[6];

        rotateface(redside, 0);
    }

    void pyraminx::backcornercounterplus(int k)
    {
        switch(k)
        {
            case 1:
            backcornercounter();
            break;

            case 2:
            backcornercounter();
            backrow1counter();
            break;

            case 3:
            backcornercounter();
            backrow1counter();
            backrow2counter();
            break;
        }
    }

    void pyraminx::backcornerplus(int k)
    {
        switch(k)
        {
            case 1:
            backcorner();
            break;

            case 2:
            backcorner();
            backrow1();
            break;

            case 3:
            backcorner();
            backrow1();
            backrow2();
            break;
        }
    }


    std::vector<pyraminx> pyraminx::getNeighbors() 
    {
        std::vector<pyraminx> neighbors;

        // Create 12 neighbors by copying the current state
        for (int i = 0; i < 12; i++) 
        {
            pyraminx neighbor = *this; // Directly copy the current state
            neighbors.push_back(neighbor);
        }

        // Apply moves to generate new states
        neighbors[0].topcornerplus(1);
        neighbors[1].topcornerplus(2);
        neighbors[2].topcornerplus(3);

        neighbors[3].leftcornerplus(1);
        neighbors[4].leftcornerplus(2);
        neighbors[5].leftcornerplus(3);

        neighbors[6].rightcornerplus(1);
        neighbors[7].rightcornerplus(2);
        neighbors[8].rightcornerplus(3);

        neighbors[9].backcornerplus(1);
        neighbors[10].backcornerplus(2);
        neighbors[11].backcornerplus(3);

        return neighbors;
    }


//the printpyraminx function will print the pyraminx as it was shown in the comment at the beginning of the file
//red being the center, green left, yellow right, blue bottom
    void pyraminx::printpyraminx()
    {
        std::cout<<std::setw(10)<<greenside[0]<<std::setw(10)<< redside[0]<<std::setw(10)<< yellowside[0]<<std::endl;

        std::cout<<std::setw(9)<<greenside[1]<<greenside[2]<<greenside[3]<<std::setw(8)<< redside[1]<<redside[2]<<redside[3]
        <<std::setw(8)<< yellowside[1]<<yellowside[2]<<yellowside[3]<<std::endl;

        std::cout<<std::setw(8)<<greenside[4]<<greenside[5]<<greenside[6]<<greenside[7]<<greenside[8]
        <<std::setw(6)<< redside[4]<<redside[5]<<redside[6]<<redside[7]<<redside[8]
        <<std::setw(6)<< yellowside[4]<<yellowside[5]<<yellowside[6]<<yellowside[7]<<yellowside[8]<<std::endl;

        std::cout<<std::setw(7)<<greenside[9]<<greenside[10]<<greenside[11]<<greenside[12]<<greenside[13]<<greenside[14]<<greenside[15]
        <<std::setw(4)<< redside[9]<<redside[10]<<redside[11]<<redside[12]<<redside[13]<<redside[14]<<redside[15]
        <<std::setw(4)<< yellowside[9]<<yellowside[10]<<yellowside[11]<<yellowside[12]<<yellowside[13]<<yellowside[14]<<yellowside[15]<<std::endl;

        std::cout<<std::setw(17)<<blueside[15]<<blueside[14]<<blueside[13]<<blueside[12]<<blueside[11]<<blueside[10]<<blueside[9]<<std::endl;
        std::cout<<std::setw(18)<<blueside[8]<<blueside[7]<<blueside[6]<<blueside[5]<<blueside[4]<<std::endl;
        std::cout<<std::setw(19)<<blueside[3]<<blueside[2]<<blueside[1]<<std::endl;
        std::cout<<std::setw(20)<<blueside[0]<<std::endl;
    }


//the scramble function takes a number of moves to do and then
//gets a random number and then does mod32 on it to decide what move to do numberofmoves times
    void pyraminx::scramble(int numberofmoves)
    {
        for(int i=0; i<numberofmoves; i++)
        {
            int randomnumber = rand()%12+1;
            switch(randomnumber)
            {
                case 1:
                topcornercounterplus(1);
                break;

                case 2:
                topcornercounterplus(2);
                break;

                case 3:
                topcornercounterplus(3);
                break;

                case 4:
                leftcornercounterplus(1);
                break;

                case 5:
                leftcornercounterplus(2);
                break;

                case 6:
                leftcornercounterplus(3);
                break;

                case 7:
                rightcornercounterplus(1);
                break;

                case 8:
                rightcornercounterplus(2);
                break;

                case 9:
                rightcornercounterplus(3);
                break;

                case 10:
                backcornercounterplus(1);
                break;

                case 11:
                backcornercounterplus(2);
                break;

                case 12:
                backcornercounterplus(3);
                break;

            }
        }
    }

    bool pyraminx::operator==(const pyraminx& other) const 
    {
        return (redside == other.redside &&
                greenside == other.greenside &&
                yellowside == other.yellowside &&
                blueside == other.blueside);
    }