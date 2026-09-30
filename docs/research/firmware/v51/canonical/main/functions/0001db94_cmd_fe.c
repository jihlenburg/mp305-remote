/* Address: 0001db94; name: cmd_fe; body bytes: 82 */

undefined4 cmd_fe(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_2 = 0xff;
  if ((*(char *)(param_1 + 1) == -0x56) && (*(char *)(param_1 + 2) == 'U')) {
    param_2[1] = 0xaa;
    param_2[2] = 0x55;
    FUN_0001dbe8();
    FUN_0001ca60(200);
  }
  else {
    param_2[1] = 0;
    param_2[2] = 0;
  }
  uVar1 = 3;
  if (param_3 == 6) {
    uVar1 = 4;
    param_2[3] = *(undefined1 *)(param_1 + param_4 + -1);
  }
  return uVar1;
}

