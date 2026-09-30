/* Address: ram:0004ff34; name: FUN_ram_0004ff34; body bytes: 198 */

undefined4 FUN_ram_0004ff34(undefined1 param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  uVar3 = 2;
  if ((param_3 != (undefined1 *)0x0) && (param_2 != (undefined1 *)0x0)) {
    *param_3 = param_1;
    param_3[1] = *param_2;
    param_3[2] = param_2[1];
    param_3[3] = param_2[2];
    uVar1 = param_2[3];
    param_3[5] = 0;
    param_3[4] = uVar1;
    bVar2 = (byte)((ushort)*(undefined2 *)(param_2 + 4) >> 8) & 1;
    param_3[5] = bVar2;
    if ((*(ushort *)(param_2 + 4) & 0x200) != 0) {
      param_3[5] = bVar2 | 2;
    }
    if ((*(ushort *)(param_2 + 4) & 0x400) != 0) {
      param_3[5] = param_3[5] | 4;
    }
    if ((int)((uint)*(ushort *)(param_2 + 4) << 0x14) < 0) {
      param_3[5] = param_3[5] | 8;
    }
    param_3[6] = 0;
    bVar2 = param_2[4];
    param_3[6] = bVar2 & 1;
    if ((*(ushort *)(param_2 + 4) & 2) != 0) {
      param_3[6] = bVar2 & 1 | 2;
    }
    if ((*(ushort *)(param_2 + 4) & 4) != 0) {
      param_3[6] = param_3[6] | 4;
    }
    uVar3 = 0;
    if ((*(ushort *)(param_2 + 4) & 8) != 0) {
      param_3[6] = param_3[6] | 8;
    }
  }
  return uVar3;
}

