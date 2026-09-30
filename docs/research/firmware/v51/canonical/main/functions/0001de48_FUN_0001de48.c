/* Address: 0001de48; name: FUN_0001de48; body bytes: 54 */

undefined4 FUN_0001de48(int param_1,char *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0xfffffffd;
  if (param_2 != (char *)0x0) {
    if (*param_2 == '\0') {
      *(char *)(param_1 + 0x80) = param_2[2] | param_2[3] | param_2[1];
    }
    else {
      *(undefined2 *)(param_1 + 0x88) = *(undefined2 *)(param_2 + 4);
      *(undefined2 *)(param_1 + 0x8c) = *(undefined2 *)(param_2 + 6);
    }
    *(char *)(param_1 + 0x81) = param_2[0xc];
    *(undefined2 *)(param_1 + 4) = *(undefined2 *)(param_2 + 8);
    uVar1 = 0;
  }
  return uVar1;
}

