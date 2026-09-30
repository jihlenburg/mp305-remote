/* Address: CODE:4920; name: FUN_CODE_4920; body bytes: 207 */

void FUN_CODE_4920(void)

{
  char cVar1;
  byte bVar2;
  char in_PSW;
  undefined *puVar3;
  
  FUN_CODE_a6f7();
  BANK2_R7 = BANK0_R7;
  FUN_CODE_a5dd(3);
  if (in_PSW < '\0') {
LAB_CODE_49b2:
    BANK2_R6 = 7;
  }
  else {
    FUN_CODE_a60e(0xc);
    if (in_PSW < '\0') {
      thunk_FUN_CODE_7bca(0);
    }
    else {
      FUN_CODE_a60e(0xf);
      if (in_PSW < '\0') {
        if (BANK2_R7 == '\x06') goto LAB_CODE_49b2;
        if (BANK2_R7 == '\x04') {
          BANK2_R6 = 1;
          goto LAB_CODE_4a18;
        }
      }
      else {
        FUN_CODE_a5dd(5);
        if (in_PSW < '\0') {
          cVar1 = FUN_CODE_4a33(2);
        }
        else {
          FUN_CODE_a5dd(7);
          if (in_PSW < '\0') {
            cVar1 = FUN_CODE_4a22(2);
          }
          else {
            FUN_CODE_a5dd(4);
            if (in_PSW < '\0') {
              cVar1 = FUN_CODE_4a33(1);
            }
            else {
              FUN_CODE_a5dd(6);
              if (-1 < in_PSW) {
                cVar1 = '\x1a';
                FUN_CODE_a607();
                if (in_PSW < '\0') {
                  if ((BANK2_R7 == '\x02') && (FUN_CODE_a356(), cVar1 == '\x02')) {
                    FUN_CODE_a02d(0x1a);
                    goto LAB_CODE_49b2;
                  }
                  FUN_CODE_9e27(3);
                  if (((BANK2_R7 != '\x03') && (BANK2_R7 != '\x06')) &&
                     (BANK2_R6 = 7, BANK2_R7 != '\a')) goto LAB_CODE_4a18;
                }
                goto LAB_CODE_49d2;
              }
              cVar1 = FUN_CODE_4a22(1);
            }
          }
        }
        if (cVar1 != '\0') goto LAB_CODE_4a18;
      }
    }
LAB_CODE_49d2:
    bVar2 = BANK2_R7 - 1;
    if (bVar2 < 7) {
      puVar3 = &UNK_CODE_49e5;
      if (CARRY1(bVar2,bVar2)) {
        puVar3 = (undefined *)0x4ae5;
      }
                    /* WARNING: Could not recover jumptable at 0x49e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(puVar3 + bVar2 * '\x02'))();
      return;
    }
  }
LAB_CODE_4a18:
  FUN_CODE_25d4(BANK2_R6,BANK2_R7);
  return;
}

