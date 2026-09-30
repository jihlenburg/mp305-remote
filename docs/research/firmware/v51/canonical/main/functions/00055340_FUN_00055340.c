/* Address: 00055340; name: FUN_00055340; body bytes: 98 */

void FUN_00055340(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_1ffe034c != 0) {
    if (DAT_1ffe02c8 != param_1) {
      uVar2 = (param_1 % 0xe10) / 0x3c;
      uVar1 = (param_1 % 0xe10) % 0x3c;
      DAT_1ffe02c8 = param_1;
      FUN_000499de(DAT_1ffe037c,"%03ld:%02ld:%02ld",param_1 / 0xe10,uVar2,uVar1);
      FUN_000499de(DAT_1ffe0588,"%03ld:%02ld:%02ld",param_1 / 0xe10,uVar2,uVar1);
    }
    return;
  }
  DAT_1ffe02c8 = 0xffffffff;
  return;
}

