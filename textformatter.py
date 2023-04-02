# kitsah code

import math
import sys

PIXEL_LIMIT = 110
PIXELS_PER_LETTER = 5

def main():
    result = ""

    filename = ""
    if len(sys.argv) == 0 or len(sys.argv) > 1:
        print("ERROR! Provide a file and ensure only one file is provided!")
    else:
        filename = sys.argv[0]
    
    with open(filename, "r+") as f:
        consumed_pixels = 0
        
        # Convert Windows line terminators to Unix-style.
        txt = f.read().replace("\r\n", "\n")
        
        # Strip succeeding spaces from each line
        txt = "\n".join(l.rstrip(" ") if l.endswith(" ") else l for l in txt.splitlines())
        
        # Loop through each word in the string whilst stripping newlines from the beginning.
        for word in [w.lstrip("\n") for w in txt.split(" ")]:
            # Calculate the quantity of pixels that need to be allocated.
            pixels = len(word) * PIXELS_PER_LETTER
            
            # If the word will overflow, append & wrap when needed
            # (consumed pixels + pixels of this word + pixel length of a dash ("-"))
            if consumed_pixels + pixels + PIXELS_PER_LETTER > PIXEL_LIMIT:
                # Calc num of overflows and change wrapping style as necessary — pixels / PPL = number of lines = no. of overflows.
                num_overflows = math.ceil(pixels / PIXEL_LIMIT)
                if num_overflows == 1:
                    result += "\n"
                    consumed_pixels = 0
                    for l in word:
                        if l == "\n":
                            consumed_pixels = 0
                        else:
                            consumed_pixels += PIXELS_PER_LETTER
                        result += l
                else:
                    for l in word:
                        # If the letter is a newline, add a newline and reset pixel consumption counter
                        if l == "\n":
                            result += l
                            consumed_pixels = 0
                        else:
                            # Checks if the letter followed by a dash will cause an overflow or not, if so, prepare to wrap.
                            if consumed_pixels + PIXELS_PER_LETTER * 2 > PIXEL_LIMIT:
                                result += "-\n" + l
                                consumed_pixels = PIXELS_PER_LETTER
                            else:
                                result += l
                                consumed_pixels += PIXELS_PER_LETTER
                                
                result += " "
                consumed_pixels += PIXELS_PER_LETTER # The additional space accounts for 1 addit. pixel.
            else:
                result += word + " "
                # Pixels of word + pixel length of a space (" ")
                consumed_pixels += pixels + PIXELS_PER_LETTER
                        
        
        f.seek(0)
        f.truncate(0)
        f.write(result)
    

if __name__ == "__main__":
    main()


