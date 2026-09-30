/* Address: 00024664; name: FUN_00024664; body bytes: 86 */

void FUN_00024664(int param_1)

{
  undefined1 auStack_60 [88];
  
  if (*(int *)(param_1 + 0x44) != 0) {
    FUN_0003c9f8(auStack_60);
    FUN_0003cb2a(auStack_60,param_1);
    FUN_0003cafa(auStack_60,&DAT_0005a071);
    FUN_0003caea(auStack_60,*(undefined4 *)(param_1 + 0x44));
    FUN_0003cb1e(auStack_60,0,1);
    FUN_0003cafe(auStack_60,0x3cabd);
    FUN_0003cadc(auStack_60,0x5a073);
    FUN_0003cb6c(auStack_60);
    return;
  }
  FUN_00059fec();
  return;
}

