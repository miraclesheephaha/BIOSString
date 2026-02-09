CHAR8* ConvertChar16toChar8(CHAR16 *InputString16)
{
    CHAR8 *OutString8 = (CHAR8 *)NULL;
    UINTN Strlen16 = 0;
    UINTN Index = 0;
    /*
      檢查呼叫者傳進來的東西，既然沒有原料，我就不浪費時間去申請記憶體了。
      */
    if ((NULL == InputString16) || (*InputString16 == L'\0'))
    {
        return (CHAR8*)NULL;
    }
    /*
      StrLen計算內容個數假設"ABC"回傳3，StrLen是取存放內容的第一個位址，直到遇到\0停止運算。
      sizeof是計算一個byte的個數。
      
      "ABC" 來跑一遍那行公式： AllocateZeroPool((Strlen16 + 1) * sizeof(CHAR8))
      1. Strlen16：回傳 3（因為有 A, B, C）。
      2. + 1：變成 4（預留一個位置給 \0）。
      3. * sizeof(CHAR8)：變成 $4 \times 1 = 4$。
      StrLen 算個數，sizeof 算單位大小
      */
    Strlen16 = StrLen(InputString16);
    OutString8 = AllocateZeroPool((Strlen16+1) * sizeof(CHAR8));
    /*
      即便「原料」很完美（例如傳入 L"Hello"），但在執行 AllocateZeroPool 時，電腦的記憶體可能剛好被其他程式塞滿了。
      用意：「雖然我有原料，但系統不給我新宿舍，所以我沒辦法搬家。」
      */
    if (NULL != OutString8){
        while(InputString16[Index] != L'\0')
        {
            OutString8[Index] = (CHAR8)InputString16[Index];
            Index++;
        }

        OutString8[Index] = '\0';
    }
    return OutString8;
}
