#include <stdio.h>
#include <ctype.h>

/* Converts a hex character to its integer value */
static char from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/* Converts an integer value to its hex character */
static char to_hex(char code) {
    static char hex[] = "0123456789abcdef";
    return hex[code & 15];
}

void url_encode() {
    char c;
    while( EOF != ( c = getchar() ) ) {
        if( isalnum( c ) || c == '-' || c == '_' || c == '.' || c == '~') 
            putchar( c );
        else if( c == ' ' ) 
            putchar( '+' );
        else {
            putchar( '%' );
            putchar( to_hex( c >> 4 ) );
            putchar( to_hex( c & 15 ) );
        }
    }
}

void url_decode() {
    char c;
    while( EOF != ( c = getchar() ) ) {
        if( c == '%' ) {
            char h1, h2;
            if(    EOF != ( h1 = getchar() )
                && EOF != ( h2 = getchar() )
              ) {
                char out = from_hex( h1 ) << 4 | from_hex( h2 );
                putchar( out );
            }
        } else if( c == '+' ) { 
            putchar( ' ' );
        } else {
            putchar( c );
        }
    }
}

int main( int argc, char **argv ) {
    if( argc < 2 ) return 1;
    if( *argv[1] == 'e' )
        url_encode();
    else if( *argv[1] == 'd' )
        url_decode();
    else return 2;
    return 0;
}

