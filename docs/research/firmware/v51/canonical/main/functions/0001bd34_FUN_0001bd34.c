/* Address: 0001bd34; name: FUN_0001bd34; body bytes: 146 */

undefined4 FUN_0001bd34(int param_1,uint *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = 0xfffffffd;
  if (param_2 != (uint *)0x0) {
    if (*param_2 == 0) {
      *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) & 0xffffdfff;
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0x8fffffff;
    }
    else {
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0x8fffffff | *param_2 & 0x70000000;
      *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 0x2000;
    }
    if (param_2[1] == 0) {
      *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) & 0xffffbfff;
      uVar2 = *(uint *)(param_1 + 0xc) & 0xf8ffffff;
    }
    else {
      *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 0x4000;
      uVar2 = *(uint *)(param_1 + 0xc) & 0xf8ffffff | param_2[1] & 0x7000000;
    }
    *(uint *)(param_1 + 0xc) = uVar2;
    if (param_2[2] == 0) {
      *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) & 0xffff7fff;
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xff8fffff;
    }
    else {
      *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 0x8000;
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xff8fffff | param_2[2] & 0x700000;
    }
    uVar1 = 0;
  }
  return uVar1;
}

