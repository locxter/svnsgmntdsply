# svnsgmntdsply

## Overview

![Overview image](overview.png)

This is a simple ESP8266-driven seven-segment display.

## Dependencies

I generally try to minimize dependencies, but I'm a one man crew and can therefore only support Debian-based Linux distributions as I'm running one myself. Anyway, you need to have the following packages installed for everything to work properly:

- Arduino IDE as a way to compile the Arduino code. Install it with `sudo apt install arduino`.
- Arduino ESP8266 LittleFS uploader for uploading the data. Install it via the [installation guide](https://github.com/earlephilhower/arduino-esp8266littlefs-plugin).

## How to build it

Simply wire the ESP up to the display like this:

![Display datasheet](images/display-datasheet.png)

| Display pin: | ESP8266 pin: |
| --- | --- |
| 1 | D0 |
| 2 | D0 inverted with NOT gate |
| 9 | 1 (TX) |
| 10 | 3 (RX) |
| 12 | D8 |
| 13 | D7 |
| 15 | D6 |
| 16 | D5 |
| 17 | D4 |
| 18 | D3 |
| 19 | D2 |
| 20 | D1 |
| 21 | 10 (SD3) |

Personally, I soldered this simple circuit on a piece of perfboard. Not the most beautiful thing ever made, but it works:

![Circuit on perfboard](perfboard.png)

## How to use it

1. Put your Wi-Fi credentials into the code and flash the sketch.
2. Upload the additional files via the Arduino ESP8266 LittleFS uploader.
3. Power the ESP on and give it roughly half a minute to boot up.
4. Open `svnsgmntdsply.local` (or enter the IP address of the ESP manually) on a device that is connected to the same network.
5. Enter a text you like (see available characters down below) and enjoy the glory of seven-segment displays.

## Segment labels

![Segment labels](images/segment-labels.svg)

## Number codes

| Number: | Code (ABCDEFG): | Preview: |
| --- | --- | --- |
| 0 | 1111110 | ![0](images/number-0.svg) |
| 1 | 0110000 | ![1](images/number-1.svg) |
| 2 | 1101101 | ![2](images/number-2.svg) |
| 3 | 1111001 | ![3](images/number-3.svg) |
| 4 | 0110011 | ![4](images/number-4.svg) |
| 5 | 1011011 | ![5](images/number-5.svg) |
| 6 | 1011111 | ![6](images/number-6.svg) |
| 7 | 1110000 | ![7](images/number-7.svg) |
| 8 | 1111111 | ![8](images/number-8.svg) |
| 9 | 1111011 | ![9](images/number-9.svg) |

## Uppercase letter codes

| Letter: | Code (ABCDEFG): | Preview: |
| --- | --- | --- |
| A | 1110111 | ![A](images/uppercase-letter-a.svg) |
| B | 1111111 | ![B](images/uppercase-letter-b.svg) |
| C | 1001110 | ![C](images/uppercase-letter-c.svg) |
| D | 1111100 | ![D](images/uppercase-letter-d.svg) |
| E | 1001111 | ![E](images/uppercase-letter-e.svg) |
| F | 1000111 | ![F](images/uppercase-letter-f.svg) |
| G | 1011110 | ![G](images/uppercase-letter-g.svg) |
| H | 0110111 | ![H](images/uppercase-letter-h.svg) |
| I | 0000110 | ![I](images/uppercase-letter-i.svg) |
| J | 0111000 | ![J](images/uppercase-letter-j.svg) |
| K | 1010111 | ![K](images/uppercase-letter-k.svg) |
| L | 0001110 | ![L](images/uppercase-letter-l.svg) |
| M | 1101010 | ![M](images/uppercase-letter-m.svg) |
| N | 1110110 | ![N](images/uppercase-letter-n.svg) |
| O | 1111110 | ![O](images/uppercase-letter-o.svg) |
| P | 1100111 | ![P](images/uppercase-letter-p.svg) |
| Q | 1101011 | ![Q](images/uppercase-letter-q.svg) |
| R | 1101111 | ![R](images/uppercase-letter-r.svg) |
| S | 1011011 | ![S](images/uppercase-letter-s.svg) |
| T | 1000110 | ![T](images/uppercase-letter-t.svg) |
| U | 0111110 | ![U](images/uppercase-letter-u.svg) |
| V | 0111010 | ![V](images/uppercase-letter-v.svg) |
| W | 1011100 | ![W](images/uppercase-letter-w.svg) |
| X | 1001001 | ![X](images/uppercase-letter-x.svg) |
| Y | 0101011 | ![Y](images/uppercase-letter-y.svg) |
| Z | 1101101 | ![Z](images/uppercase-letter-z.svg) |

## Lowercase letter codes

| Letter: | Code (ABCDEFG): | Preview: |
| --- | --- | --- |
| a | 0011001 | ![a](images/lowercase-letter-a.svg) |
| b | 0011111 | ![b](images/lowercase-letter-b.svg) |
| c | 0001101 | ![c](images/lowercase-letter-c.svg) |
| d | 0111101 | ![d](images/lowercase-letter-d.svg) |
| e | 0001100 | ![e](images/lowercase-letter-e.svg) |
| f | 0000111 | ![f](images/lowercase-letter-f.svg) |
| g | 1001101 | ![g](images/lowercase-letter-g.svg) |
| h | 0010111 | ![h](images/lowercase-letter-h.svg) |
| i | 1001100 | ![i](images/lowercase-letter-i.svg) |
| j | 1011000 | ![j](images/lowercase-letter-j.svg) |
| k | 1001011 | ![k](images/lowercase-letter-k.svg) |
| l | 0000110 | ![l](images/lowercase-letter-l.svg) |
| m | 1010101 | ![m](images/lowercase-letter-m.svg) |
| n | 0010101 | ![n](images/lowercase-letter-n.svg) |
| o | 0011101 | ![o](images/lowercase-letter-o.svg) |
| p | 1100111 | ![p](images/lowercase-letter-p.svg) |
| q | 1110011 | ![q](images/lowercase-letter-q.svg) |
| r | 0000101 | ![r](images/lowercase-letter-r.svg) |
| s | 0011000 | ![s](images/lowercase-letter-s.svg) |
| t | 0001111 | ![t](images/lowercase-letter-t.svg) |
| u | 0011100 | ![u](images/lowercase-letter-u.svg) |
| v | 0011000 | ![v](images/lowercase-letter-v.svg) |
| w | 0101010 | ![w](images/lowercase-letter-w.svg) |
| x | 0001001 | ![x](images/lowercase-letter-x.svg) |
| y | 0111011 | ![y](images/lowercase-letter-y.svg) |
| z | 0001001 | ![z](images/lowercase-letter-z.svg) |

## Other character codes

| Character: | Code (ABCDEFG): | Preview: |
| --- | --- | --- |
| Space ( ) | 0000000 | ![Space ( )](images/other-character-space.svg) |
| Underscore (_) | 0001000 | ![Underscore (_)](images/other-character-underscore.svg) |
| Hyphen-minus (-) | 0000001 | ![Hyphen-minus (-)](images/other-character-hyphen-minus.svg) |
| Equals (=) | 0001001 | ![Equals (=)](images/other-character-equals.svg) |
| Double quote (") | 0100010 | ![Double quote (") ](images/other-character-double-quote.svg) |
| Single quote (') | 0000010 | ![Single quote (')](images/other-character-single-quote.svg) |
| Open parenthesis (() | 1001110 | ![Open parenthesis (() ](images/other-character-open-parenthesis.svg) |
| Close parenthesis ()) | 1111000 | ![Close parenthesis ())](images/other-character-close-parenthesis.svg) |
| Question mark (?) | 1100101 | ![Question mark (?)](images/other-character-question-mark.svg) |

## Current paths

| Segment (digit - segment): | Current path (GND pin - VCC pin): |
| --- | --- |
| AM | 1-5 |
| PM | 3-4 |
| 1-A | 1-7 |
| 1-B | 2-6 |
| 1-C | 2-9 |
| 1-D | 1-8 |
| 1-E | 2-8 |
| 1-F | Does not exist |
| 1-G | 2-7 |
| 2-A | 2-13 |
| 2-B | 2-10 |
| 2-C | 2-12 |
| 2-D | 1-12 |
| 2-E | 1-9 |
| 2-F | 1-13 |
| 2-G | 1-10 |
| Colon | 1-30 |
| 3-A | 1-15 |
| 3-B | 1-16 |
| 3-C | 1-17 |
| 3-D | 2-17 |
| 3-E | 2-18 |
| 3-F | 2-15 |
| 3-G | 2-16 |
| 4-A | 2-21 |
| 4-B | 2-19 |
| 4-C | 2-20 |
| 4-D | 1-20 |
| 4-E | 1-18 |
| 4-F | 1-21 |
| 4-G | 1-19 |
| Alarm | 28-27 |

## Sources

- https://en.wikipedia.org/wiki/Seven-segment_display
- https://en.wikipedia.org/wiki/Seven-segment_display_character_representations
- https://libesz.digitaltrip.hu/digital-clock/
