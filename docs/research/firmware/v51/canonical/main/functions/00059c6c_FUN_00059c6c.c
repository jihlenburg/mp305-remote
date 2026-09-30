/* Address: 00059c6c; name: FUN_00059c6c; body bytes: 58 */

void FUN_00059c6c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(DAT_1ffe004c + 0xc) + 0xc);
  FUN_00065666(iVar1 + 4);
  if ((int)((uint)*(byte *)(iVar1 + 0x24) << 0x1d) < 0) {
    FUN_00059dfc(iVar1,param_1,param_2);
  }
  else {
    *(byte *)(iVar1 + 0x24) = *(byte *)(iVar1 + 0x24) & 0xfe;
  }
                    /* WARNING: Could not recover jumptable at 0x00059ca4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x20))(iVar1);
  return;
}

