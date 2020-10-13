#include <LiquidCrystal.h>
#include <stdio.h>
#include <ctype.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char m_Output[] = "bom dia ufpe";

char morseCodeString[16];
float timeUnit = 500;
int previousCharPosition = 777;
int previousBottomCharPosition = 777;
bool bottomRowRefresh = true;

void setup()
{
    lcd.begin(16, 2);
    pinMode(13, OUTPUT);
}

void loop()
{
    lcd.clear();
    lcd.print(m_Output);
    readPhrase(m_Output);
}

void readPhrase(char myPhrase[])
{
    for (int i = 0; i < strlen(myPhrase); i++)
    {
        convertCharToMorse(myPhrase[i], i);
        delay(timeUnit * 2); // Delay after each char
    }
    // Delay after a word is done being transmited as morse code.
    delay(timeUnit * 10);
}

void convertCharToMorse(char myChar, int position)
{
    switch (myChar)
    {
    case 'a':
        Beeper2(position, 1, 3);
        break;
    case 'b':
        Beeper4(position, 3, 1, 1, 1);
        break;
    case 'c':
        Beeper4(position, 3, 1, 3, 1);
        break;
    case 'd':
        Beeper3(position, 3, 1, 1);
        break;
    case 'e':
        Beeper1(position, 1);
        break;
    case 'f':
        Beeper4(position, 1, 1, 3, 1);
        break;
    case 'g':
        Beeper3(position, 3, 3, 1);
        break;
    case 'h':
        Beeper4(position, 1, 1, 1, 1);
        break;
    case 'i':
        Beeper2(position, 1, 1);
        break;
    case 'j':
        Beeper4(position, 1, 3, 3, 3);
        break;
    case 'k':
        Beeper3(position, 3, 1, 3);
        break;
    case 'l':
        Beeper4(position, 1, 3, 1, 1);
        break;
    case 'm':
        Beeper2(position, 3, 3);
        break;
    case 'n':
        Beeper2(position, 3, 1);
        break;
    case 'o':
        Beeper3(position, 3, 3, 3);
        break;
    case 'p':
        Beeper4(position, 1, 3, 3, 1);
        break;
    case 'q':
        Beeper4(position, 3, 3, 1, 3);
        break;
    case 'r':
        Beeper3(position, 1, 3, 1);
        break;
    case 's':
        Beeper3(position, 1, 1, 1);
        break;
    case 't':
        Beeper1(position, 3);
        break;
    case 'u':
        Beeper3(position, 1, 1, 3);
        break;
    case 'v':
        Beeper4(position, 1, 1, 1, 3);
        break;
    case 'w':
        Beeper3(position, 1, 3, 3);
        break;
    case 'x':
        Beeper4(position, 3, 1, 1, 3);
        break;
    case 'y':
        Beeper4(position, 3, 1, 3, 3);
        break;
    case 'z':
        Beeper4(position, 3, 3, 1, 1);
        break;

    case '1':
        Beeper5(position, 1, 3, 3, 3, 3);
        break;
    case '2':
        Beeper5(position, 1, 1, 3, 3, 3);
        break;
    case '3':
        Beeper5(position, 1, 1, 1, 3, 3);
        break;
    case '4':
        Beeper5(position, 1, 1, 1, 1, 3);
        break;
    case '5':
        Beeper5(position, 1, 1, 1, 1, 1);
        break;
    case '6':
        Beeper5(position, 3, 1, 1, 1, 1);
        break;
    case '7':
        Beeper5(position, 3, 3, 1, 1, 1);
        break;
    case '8':
        Beeper5(position, 3, 3, 3, 1, 1);
        break;
    case '9':
        Beeper5(position, 3, 3, 3, 3, 1);
        break;
    case '0':
        Beeper5(position, 3, 3, 3, 3, 3);
        break;
    case ' ':
        BeeperSpace(position);
        break;

    default:
        break;
    }
}

// ? Como faz pra fazer function overloading em C ?
void Beeper1(int positionInString, int a)
{
    int temp[] = {a};
    int tempSize = sizeof(temp) / sizeof(int);

    Beep(positionInString, temp, tempSize);
}

void Beeper2(int positionInString, int a, int b)
{
    int temp[] = {a, b};
    int tempSize = sizeof(temp) / sizeof(int);

    Beep(positionInString, temp, tempSize);
}

void Beeper3(int positionInString, int a, int b, int c)
{
    int temp[] = {a, b, c};
    int tempSize = sizeof(temp) / sizeof(int);

    Beep(positionInString, temp, tempSize);
}

void Beeper4(int positionInString, int a, int b, int c, int d)
{
    int temp[] = {a, b, c, d};
    int tempSize = sizeof(temp) / sizeof(int);

    Beep(positionInString, temp, tempSize);
}

void Beeper5(int positionInString, int a, int b, int c, int d, int e)
{
    int temp[] = {a, b, c, d, e};
    int tempSize = sizeof(temp) / sizeof(int);

    Beep(positionInString, temp, tempSize);
}

void BeeperSpace(int positionInString)
{
    int temp[0];
    int tempSize = 0;
    Beep(positionInString - 1, temp, tempSize);
    delay(timeUnit * 4);
    lcd.setCursor(positionInString - 1, 0);
    lcd.print(m_Output[positionInString - 1]);
}

void Beep(int charPositionInString, int morseCode[], int morseCodeSize)
{
    bottomRowRefresh = true;

    int count = 0;
    for (int i = 0; i < morseCodeSize; i++)
    {
        for (int j = 0; j < morseCode[i]; j++)
        {
            morseCodeString[count] = '_';
            count++;
        }
        morseCodeString[count] = ' ';
        count++;
    }

    for (int i = count; i < 16; i++)
    {
        morseCodeString[i] = ' ';
    }

    UpdateTopRow(charPositionInString);

    count = 0;
    int morseCodeStringSize = sizeof(morseCodeStringSize) / sizeof(char);
    for (int i = 0; i < morseCodeSize; i++)
    {
        digitalWrite(13, HIGH);

        for (int j = 0; j < morseCode[i]; j++)
        {
            UpdateBottomRow(morseCodeString, morseCodeStringSize, count);
            count++;
            delay(timeUnit);
        }
        digitalWrite(13, LOW);
        UpdateBottomRow(morseCodeString, morseCodeStringSize, count);
        count++;
        delay(timeUnit);
    }
    delay(timeUnit * 2);
}

void UpdateTopRow(int charPositionInString)
{
    char upperCase;
    upperCase = toupper(m_Output[charPositionInString]);

    lcd.setCursor(charPositionInString, 0);
    lcd.print(upperCase);

    if (charPositionInString > 0)
    {
        lcd.setCursor(charPositionInString - 1, 0);
        lcd.print(m_Output[charPositionInString - 1]);
    }
}

void UpdateBottomRow(char morseCodeString[], int morseCodeStringSize, int positionInString)
{
    if (bottomRowRefresh == true)
    {
        bottomRowRefresh = false;

        lcd.setCursor(0, 1);
        lcd.print(morseCodeString);
    }

    if (morseCodeString[positionInString] == '_')
    {
        lcd.setCursor(positionInString, 1);
        lcd.print('-');
    }

    if (positionInString > 0 && morseCodeString[positionInString - 1] != ' ')
    {
        lcd.setCursor(positionInString - 1, 1);
        lcd.print('_');
    }
    else if (positionInString > 0 && morseCodeString[positionInString - 1] == ' ')
    {
        lcd.setCursor(positionInString - 2, 1);
        lcd.print('_');
    }
}