/* Address: ram:0004c51c; name: FUN_ram_0004c51c; body bytes: 132 */

void FUN_ram_0004c51c(undefined2 *param_1,undefined2 *param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  
  gp = 0x20004000;
  tmos_memset(param_2,0,0x12);
  if (param_1 != (undefined2 *)0x0) {
    puVar3 = (undefined2 *)(DAT_ram_20001cc4 + (uint)*(byte *)(param_1 + 0xe) * 0x10);
    *param_2 = *puVar3;
    uVar1 = puVar3[3];
    param_2[1] = puVar3[1];
    param_2[2] = DAT_ram_20001a5e;
    param_2[3] = *param_1;
    param_2[4] = param_1[1];
    param_2[5] = param_1[2];
    param_2[6] = param_1[3];
    uVar2 = param_1[4];
    param_2[8] = uVar1;
    param_2[7] = uVar2;
  }
  return;
}

