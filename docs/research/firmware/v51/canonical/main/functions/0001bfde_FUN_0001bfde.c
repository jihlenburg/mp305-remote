/* Address: 0001bfde; name: FUN_0001bfde; body bytes: 110 */

undefined4 FUN_0001bfde(int param_1,uint *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0xfffffffd;
  if (((param_2 != (uint *)0x0) && ((uVar1 = param_2[2], uVar1 != 8 || (param_2[3] != 0x1000)))) &&
     ((*param_2 != 1 || ((uVar1 != 0 || ((param_2[5] != 0 && (param_2[5] != 2)))))))) {
    *(uint *)(param_1 + 4) = *param_2 | param_2[1] | uVar1 | param_2[9] | param_2[3] | param_2[4];
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffffc | (byte)param_2[10] & 3;
    if (param_2[2] == 8) {
      uVar1 = param_2[5] | param_2[6] | param_2[7] | param_2[8];
    }
    else {
      uVar1 = param_2[5] | param_2[7] | param_2[8];
    }
    *(uint *)(param_1 + 0x18) = uVar1;
    uVar2 = 0;
  }
  return uVar2;
}

