/* Address: 000476b0; name: FUN_000476b0; body bytes: 58 */

int FUN_000476b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0003f09e(DAT_2003a53c,param_2,0);
  if (iVar1 != 0) {
    iVar2 = FUN_0003f16a();
    *(undefined4 *)(iVar2 + 0xc) = param_3;
    if (*(char *)(iVar2 + 8) == '\x01') {
      uVar3 = FUN_00050a40(*(undefined4 *)(iVar2 + 4));
      *(undefined4 *)(iVar2 + 4) = uVar3;
    }
    *(undefined4 *)(iVar2 + 0x10) = param_1;
    *(undefined4 *)(iVar2 + 0x14) = param_4;
  }
  return iVar1;
}

