/* Address: 00059eac; name: FUN_00059eac; body bytes: 32 */

/* Recovered from stored Thumb pointer at 000670c8; callback identification is inferred until
   reviewed. */

void FUN_00059eac(void)

{
  undefined4 uVar1;
  
  do {
    if (*DAT_1ffe004c == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(undefined4 *)DAT_1ffe004c[3];
    }
    FUN_00059d90(uVar1,*DAT_1ffe004c == 0);
    FUN_00059cac();
  } while( true );
}

