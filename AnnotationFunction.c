//Unicode (UEFI 使用的是 UCS-2 / UTF-16，16 位元)，ASCII (8 位元)
//成功地將原本需要 2 Bytes 儲存的內容，壓縮進了 1 Byte 的櫃子裡
//函式通常只用於處理 BIOS 變數名稱、序號、型號 等通常只會出現 ASCII 字元的欄位。
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
      3. * sizeof(CHAR8)：變成 4x1 = 4。
      4. 最終結果：跟系統要了 4 個 Bytes 的空間。
      這行寫成 sizeof(CHAR16)，結果會變成 4 x 2 = 8 Bytes。
      雖然 StrLen 同樣回傳 3，但因為**單位（sizeof）**變了
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
            //強制轉型將Char16改成Char8並放入OutString8[Index]
            //來源 (InputString16[Index]): 它的型別是 CHAR16，在記憶體中佔 16 位元 (2 Bytes)
            //目的地 (OutString8[Index]): 它的型別是 CHAR8，在記憶體中只佔 8 位元 (1 Byte)。
            OutString8[Index] = (CHAR8)InputString16[Index];
            Index++;
        }

        OutString8[Index] = '\0';
    }
    return OutString8;
}

/*
    %a	ASCII 字串	    CHAR8 *	        "Hello"
    %s	Unicode 字串	CHAR16 *	    L"Hello"
    %d	十進位整數	    INT32 / INTN	100
    %x	十六進位整數	    UINT32 / UINTN	0x3F
    %p	指標 (地址)	    VOID *	        0x7FF12340
    %r	EFI 狀態碼	    EFI_STATUS	    Success
*/

