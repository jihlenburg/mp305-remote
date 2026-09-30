/* Address: ram:0004e85c; name: FUN_ram_0004e85c; body bytes: 60 */

void FUN_ram_0004e85c(int param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if ((param_1 != 0) && (puVar1 = *(undefined1 **)(param_1 + 0x6c), puVar1 != (undefined1 *)0x0)) {
    *param_2 = *puVar1;
    param_2[1] = puVar1[1];
    param_2[2] = puVar1[0x12];
    uVar2 = *(undefined4 *)(puVar1 + 0x14);
    param_2[3] = puVar1[0x18];
    *(undefined4 *)(param_2 + 4) = uVar2;
    return;
  }
  tmos_memset(param_2,0,0x10);
  return;
}

