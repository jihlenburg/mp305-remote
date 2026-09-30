/* Address: 0001693c; name: FUN_0001693c; body bytes: 76 */

undefined4 FUN_0001693c(uint *param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 != 0) {
    *param_1 = *param_1 & 0xfffffffe;
    *param_1 = *param_1 | 0x8000;
    *param_1 = *param_1 | 1;
    uVar1 = FUN_000166ec(param_1);
    *param_1 = *param_1 & 0xffffffbf;
    *param_1 = *param_1 & 0xffff7fff;
    *param_1 = *param_1 & 0xfffffffe;
    param_1[4] = param_1[4] & 0xffffefff;
    return uVar1;
  }
  return 0xfffffffd;
}

