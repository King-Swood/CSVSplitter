#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define FIELDS_MAX_COUNT    (6)
#define FIELDS_MAX_LENGTH   (50)

typedef struct {
    char fieldStrings[FIELDS_MAX_COUNT][FIELDS_MAX_LENGTH];
    int count;
}tFields;

static const tFields tFieldsDefault = {
    {0},
    0
};

bool SplitStringIntoFields(const char *inputString, tFields *fields)
{
    *fields = tFieldsDefault;

    if (strlen(inputString) == 0) {
        return false;
    }

    const char *fieldStart = inputString;
    while (true) {
        if (fields->count >= FIELDS_MAX_COUNT) {
            break;
        }

        char *comma = strstr(fieldStart, ",");
        if (comma) {
            ++comma;
            int length = comma - fieldStart - 1;
            if (length >= FIELDS_MAX_LENGTH) {
                length = FIELDS_MAX_LENGTH;
            }
            strncpy(fields->fieldStrings[fields->count], fieldStart, length);
            ++fields->count;
            fieldStart = comma;
        }
        else {
            strncpy(fields->fieldStrings[fields->count], fieldStart, FIELDS_MAX_LENGTH);
            ++fields->count;
            break;
        }
    }

    return true;
}

int main()
{
    tFields fields;
    if (SplitStringIntoFields("RowName,1,2,3,4,5", &fields)) {
        printf("String successfully split into fields:\n");
        for (int i = 0; i < fields.count; ++i) {
            printf("Field %d: %s\n", i, fields.fieldStrings[i]);
        }

        if (fields.count >= 6) {
            printf("Fields converted to ints: %s, %d, %d, %d, %d, %d\n",
                fields.fieldStrings[0],
                atoi(fields.fieldStrings[1]),
                atoi(fields.fieldStrings[2]),
                atoi(fields.fieldStrings[3]),
                atoi(fields.fieldStrings[4]),
                atoi(fields.fieldStrings[5])
                );
        }
    }
    else {
        printf("No fields found\n");
    }

    return 0;
}
