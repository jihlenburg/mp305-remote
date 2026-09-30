/* Address: CODE:4d85; name: FUN_CODE_4d85; body bytes: 167 */

void FUN_CODE_4d85(undefined1 param_1,byte param_2)

{
  undefined1 uVar1;
  byte bVar2;
  undefined1 *puVar3;
  byte *pbVar4;
  undefined2 uVar5;
  
  DAT_EXTMEM_04b7 = 3;
  DAT_EXTMEM_04b9 = *(char *)(param_2 + 0x8d);
  DAT_EXTMEM_04b6 = param_2;
  if ((param_2 == 0) || (param_2 == 1)) {
    FUN_CODE_9000();
    puVar3 = &DAT_EXTMEM_04b7;
    FUN_CODE_1f10();
    FUN_CODE_1d2a();
    *puVar3 = 0xb7;
    pbVar4 = &DAT_EXTMEM_04b7;
    FUN_CODE_1d22(DAT_EXTMEM_04b6);
    *pbVar4 = param_2;
    uVar1 = *(undefined1 *)(param_2 + 0x23);
    puVar3 = &DAT_EXTMEM_04b7;
    FUN_CODE_1d23();
    *puVar3 = uVar1;
    puVar3 = &DAT_EXTMEM_04b7;
    bVar2 = DAT_EXTMEM_04b6;
    FUN_CODE_1f56(DAT_EXTMEM_04b6 + 0x89);
    FUN_CODE_1d2a();
    *puVar3 = param_1;
    uVar1 = *(undefined1 *)CONCAT11('\a' - (((0xf3 < bVar2) << 7) >> 7),bVar2 + 0xc);
    puVar3 = &DAT_EXTMEM_04b7;
    FUN_CODE_1d23();
    *puVar3 = uVar1;
    DAT_EXTMEM_04b8 = 0;
    if ((DAT_EXTMEM_04b9 != '\0') << 7 < '\0') {
      uVar5 = 0x4b6;
      FUN_CODE_1d9b(DAT_EXTMEM_04b6);
      FUN_CODE_1dbf(DAT_EXTMEM_04b8,uVar5);
                    /* WARNING: Subroutine does not return */
      FUN_CODE_ad49();
    }
    FUN_CODE_1f30(-DAT_EXTMEM_04b9,0x4b7);
    FUN_CODE_a7c3();
  }
  return;
}

