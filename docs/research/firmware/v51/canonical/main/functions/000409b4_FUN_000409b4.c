/* Address: 000409b4; name: FUN_000409b4; body bytes: 274 */

void FUN_000409b4(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  
  if (param_1 == 0) {
    DAT_2003a430 = FUN_00040890();
  }
  else {
    DAT_2003a430 = *(int *)(param_1 + 0xc);
    FUN_00052a74();
  }
  if ((((DAT_2003a430 == 0) || (iVar2 = *(int *)(DAT_2003a430 + 0x24), iVar2 == 0)) ||
      (*(int *)(iVar2 + 0x10) == 0)) || (*(int *)(iVar2 + 0xc) == 0)) {
    return;
  }
  FUN_00040acc(DAT_2003a430,0x36,0);
  FUN_0004ef90(*(undefined4 *)(DAT_2003a430 + 0x2c0));
  if (*(int *)(DAT_2003a430 + 0x2c8) != 0) {
    FUN_0004ef90();
  }
  FUN_0004ef90(*(undefined4 *)(DAT_2003a430 + 0x2c4));
  FUN_0004ef90(*(undefined4 *)(DAT_2003a430 + 700));
  FUN_0004ef90(*(undefined4 *)(DAT_2003a430 + 0x2b8));
  if (*(int *)(DAT_2003a430 + 0x2c0) != 0) {
    FUN_0004f68c();
    FUN_0005ac84();
    FUN_0005a714();
    if (*(int *)(DAT_2003a430 + 0x25c) == 0) goto LAB_00040a5e;
    FUN_00040acc(DAT_2003a430,0x39,0);
    iVar2 = FUN_00040988(DAT_2003a430);
    if ((iVar2 != 0) && (*(char *)(DAT_2003a430 + 0x39) == '\x01')) {
      for (uVar6 = 0; uVar6 < *(uint *)(DAT_2003a430 + 0x25c); uVar6 = uVar6 + 1) {
        if (*(char *)(DAT_2003a430 + uVar6 + 0x23c) == '\0') {
          puVar1 = (undefined4 *)FUN_0004a200(DAT_2003a430 + 0x264);
          puVar3 = (undefined4 *)(uVar6 * 0x10 + 0x3c + DAT_2003a430);
          uVar4 = puVar3[1];
          uVar5 = puVar3[2];
          uVar7 = puVar3[3];
          *puVar1 = *puVar3;
          puVar1[1] = uVar4;
          puVar1[2] = uVar5;
          puVar1[3] = uVar7;
        }
      }
    }
    FUN_0004a57a(DAT_2003a430 + 0x3c,0,0x200);
    FUN_0004a57a(DAT_2003a430 + 0x23c,0,0x20);
  }
  *(undefined4 *)(DAT_2003a430 + 0x25c) = 0;
LAB_00040a5e:
  FUN_000452fc();
  FUN_00040acc(DAT_2003a430,0x37,0);
  return;
}

