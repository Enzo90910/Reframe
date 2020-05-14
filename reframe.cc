#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const float slower = 23.976/25, faster = 1 / slower;

int val(char c) {return c - '0';}

float read_time (char *s)
{
  float res = val(*s++); res *= 10;
  res += val(*s++); res *= 6;  s++; // hours
  res += val(*s++); res *= 10;
  res += val(*s++); res *= 6;  s++; // minutes
  res += val(*s++); res *= 10;
  res += val(*s++); res *= 10; s++; // secondes
  res += val(*s++); res *= 10;      // millisecondes
  res += val(*s++); res *= 10;
  res += val(*s++); res *= 10;
  res++;
  return res / 10000;
}

char chr(int i) {return i + '0';}

void write_time(float t, char *buf)
{
  int hours = t/3600;
  t -= 3600*hours;
  *buf++ = chr(hours/10); *buf++ = chr(hours%10); *buf++ = ':';
  int minutes = t/60;
  t -= 60*minutes;
  *buf++ = chr(minutes/10); *buf++ = chr(minutes%10); *buf++ = ':';
  int seconds = t;
  t -= seconds;
  *buf++ = chr(seconds/10); *buf++ = chr(seconds%10); *buf++ = ',';
  int millis = 1000.0001*t;
  *buf++ = chr(millis/100); *buf++ =chr((millis/10)%10); *buf++ = chr(millis%10);
}

int main(int argc, char *argv[])
{
  char line[100];
  if (argc != 3 || (strcmp(argv[2], "faster") && strcmp(argv[2], "slower")))
    {
      cout << "Syntaxe: " << argv[0]
           << " <srtfile> <faster | slower> "
           << endl;
      return 0;
    }

  float rate = strcmp(argv[2], "slower") ? faster : slower;
  fstream f(argv[1], ios::in | ios::out);
  for (streampos p = f.tellp(); f.getline (line, 100); p = f.tellp())
    if (line[2]==':' && isdigit(line[0]) && isdigit(line[1]))
	{
	  f.seekp(p);
	  float debut = read_time(line);
	  write_time(rate * debut, line);
	  float fin = read_time(line+17);
	  write_time(rate * fin, line+17);
	  f << line << endl;;
	}
}
