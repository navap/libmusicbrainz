/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "mb_c.h"

int main(int argc, char *argv[])
{
    musicbrainz_t o;
    int           ret;
    char          error[256], data[256], *args[3];

    if (argc < 4)
    {
        printf("Usage: authtest <user> <passwd> <track id> <trmid>\n");
        exit(0);
    }

    // Create the musicbrainz object, which will be needed for subsequent calls
    o = mb_New();

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    mb_UseUTF8(o, 0);

    // Tell the client library to print query and response info to stdout 
    mb_SetDebug(o, 0);

    // Tell the server to return 4 levels of data
    mb_SetDepth(o, 3);

    // Set the server you want to use. Defaults to www.musicbrainz.org:80
    //mb_SetServer(o, "musicbrainz.eorbit.net", 80);

    ret = mb_Authenticate(o, argv[1], argv[2]);
    if (ret == 0)
    {
        char error[256];

        mb_GetQueryError(o, error, 256);
        printf("Authentication failed: %s\n", error);
        mb_Delete(o);
        return 0;
    }

    printf("Authenticated ok.\n");

    // Set up the args for the find artist query
    args[0] = argv[3];
    args[1] = argv[4];
    args[2] = NULL;

    ret = mb_QueryWithArgs(o, MBQ_SubmitTrackTRMId, args);
    if (!ret)
    {
        mb_GetQueryError(o, error, 256);
        printf("Query failed: %s\n", error);
        mb_Delete(o);
        return 0;
    }

    printf("TRM Is submitted. Thank you.\n");

    // and clean up the musicbrainz object
    mb_Delete(o);

    return 0;
}
