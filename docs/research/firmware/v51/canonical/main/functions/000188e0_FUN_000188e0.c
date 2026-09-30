/* Address: 000188e0; name: FUN_000188e0; body bytes: 138 */

void FUN_000188e0(void)

{
  int iVar1;
  undefined1 auStack_238 [532];
  int local_24;
  
  if (DAT_1ffe01cc == '\0') {
    FUN_0001bef8(0x160000,&DAT_1fffa138,0x21c);
  }
  if (((DAT_1fffa34c != -0x55aa33cd) || (iVar1 = FUN_00015bd0(), iVar1 != DAT_1fffa350)) ||
     (DAT_1ffe01cc != '\0')) {
    DAT_1fffa34c = -0x55aa33cd;
    DAT_1fffa34a = 6;
    FUN_00018bfc();
    DAT_1fffa350 = FUN_00015bd0();
    FUN_0001bdf6(0x160000);
    FUN_0001bf3a(0x160000,&DAT_1fffa138,0x21c);
    FUN_0001bef8(0x160000,auStack_238,0x21c);
    DAT_1fffab1a = local_24 != -0x55aa33cd;
  }
  return;
}

