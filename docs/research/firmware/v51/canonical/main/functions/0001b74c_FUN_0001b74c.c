/* Address: 0001b74c; name: FUN_0001b74c; body bytes: 106 */

void FUN_0001b74c(void)

{
  uint uVar1;
  int iVar2;
  uint in_r3;
  uint uVar3;
  undefined4 local_18;
  
  uVar3 = 0;
  local_18 = in_r3;
  do {
    FUN_0001b740(&local_18,2,uVar3 * 0x80 + 0xfe000);
    uVar1 = local_18 & 0xff;
    if ((uVar1 == 0xff) && (local_18._1_1_ == -1)) {
      if (uVar3 == 0) goto LAB_0001b7b0;
      iVar2 = uVar3 * 0x80 + 0xfdf80;
LAB_0001b79e:
      FUN_0001b740(&DAT_1fffa0b8,0x80,iVar2);
      iVar2 = FUN_00015f5c();
      if (iVar2 == DAT_1fffa134) {
        return;
      }
LAB_0001b7b0:
      FUN_0001d868();
      return;
    }
    if ((uVar1 != uVar3) || (local_18._1_1_ != '\x05')) goto LAB_0001b7b0;
    if ((uVar1 == uVar3) && (uVar3 == 0x3f)) {
      iVar2 = 0xfff80;
      goto LAB_0001b79e;
    }
    uVar3 = uVar3 + 1;
    if (0x3f < uVar3) {
      return;
    }
  } while( true );
}

