/* Address: 0004f74c; name: FUN_0004f74c; body bytes: 364 */

/* WARNING: Removing unreachable block (ram,0x0004fa32) */
/* WARNING: Removing unreachable block (ram,0x0004fa58) */
/* WARNING: Removing unreachable block (ram,0x0004fa84) */
/* WARNING: Removing unreachable block (ram,0x0004fa9e) */
/* WARNING: Removing unreachable block (ram,0x0004faac) */
/* WARNING: Removing unreachable block (ram,0x0004faa6) */
/* WARNING: Removing unreachable block (ram,0x0004fa8c) */
/* WARNING: Removing unreachable block (ram,0x0004faae) */
/* WARNING: Removing unreachable block (ram,0x0004fab4) */
/* WARNING: Removing unreachable block (ram,0x0004fab8) */
/* WARNING: Removing unreachable block (ram,0x0004faca) */
/* WARNING: Removing unreachable block (ram,0x0004face) */
/* WARNING: Removing unreachable block (ram,0x0004faf2) */
/* WARNING: Removing unreachable block (ram,0x0004fadc) */
/* WARNING: Removing unreachable block (ram,0x0004faf8) */
/* Recovered from stored Thumb pointer at 0007adf8; callback identification is inferred until
   reviewed. */

void FUN_0004f74c(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(byte *)(param_2 + 0x3c) = *(byte *)(param_2 + 0x3c) & 0xfc;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  FUN_0004e00e(param_2,0x10);
  FUN_0004e00e(param_2,0x200);
  FUN_0004b144(&DAT_0007ae18,param_2);
  FUN_0004b210();
  uVar1 = FUN_0003759c(param_2);
  *(undefined4 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  for (iVar2 = 0; "Option 1\nOption 2\nOption 3\nOption 4\nOption 5"[iVar2] != '\0';
      iVar2 = iVar2 + 1) {
    if ("Option 1\nOption 2\nOption 3\nOption 4\nOption 5"[iVar2] == '\n') {
      *(int *)(param_2 + 0x2c) = *(int *)(param_2 + 0x2c) + 1;
    }
  }
  *(int *)(param_2 + 0x2c) = *(int *)(param_2 + 0x2c) + 1;
  *(byte *)(param_2 + 0x3c) = *(byte *)(param_2 + 0x3c) & 0xfc;
  FUN_00049974(uVar1,"Option 1\nOption 2\nOption 3\nOption 4\nOption 5");
  *(undefined4 *)(param_2 + 0x34) = *(undefined4 *)(param_2 + 0x30);
  FUN_0004de6c(uVar1);
  return;
}

