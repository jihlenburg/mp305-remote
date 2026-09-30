/* Address: 0005a078; name: FUN_0005a078; body bytes: 40 */

int FUN_0005a078(int param_1,uint param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + -4) = 0x1000000;
  *(uint *)(param_1 + -8) = param_2 & 0xfffffffe;
  *(undefined **)(param_1 + -0xc) = &DAT_00059e89;
  *(undefined4 *)(param_1 + -0x20) = param_3;
  *(undefined4 *)(param_1 + -0x24) = 0xfffffffd;
  return param_1 + -0x44;
}

