//
//  rem.c
//  lab4
//
//  Created by Вероника Низамова on 13.11.2020.
//  Copyright © 2020 Вероника Низамова. All rights reserved.
//

#include "rem.h"

void removeEndLine(char* client_message)
{
    int i=0;
    while((client_message[i])!='\n')
    {
        i++;
    }
    client_message[i] = '\0';
}
