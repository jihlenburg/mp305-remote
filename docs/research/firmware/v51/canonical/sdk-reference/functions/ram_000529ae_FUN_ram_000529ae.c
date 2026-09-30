/* Address: ram:000529ae; name: FUN_ram_000529ae; body bytes: 156 */

void FUN_ram_000529ae(undefined4 param_1,undefined1 *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  short sStack_34;
  ushort uStack_32;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  
  gp = 0x20004000;
  uVar2 = FUN_ram_00042934(1,0x3ffffe);
  uStack_32 = (ushort)((uVar2 | 0x400000) << 8) | (ushort)(uVar2 >> 8) & 0xff;
  bVar1 = (byte)((uVar2 | 0x400000) >> 0x10);
  sStack_34 = (ushort)bVar1 << 8;
  local_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  LL_Encrypt(param_1,&local_40,&uStack_30);
  param_2[3] = (char)uVar2;
  param_2[4] = (char)(uVar2 >> 8);
  iVar3 = (uStack_24 >> 0x10 & 0xff) * 0x100 + (uStack_24 >> 8 & 0xff) * 0x10000 +
          (uStack_24 >> 0x18);
  *param_2 = (char)iVar3;
  param_2[5] = bVar1;
  param_2[1] = (char)((uint)iVar3 >> 8);
  param_2[2] = (char)((uint)iVar3 >> 0x10);
  return;
}

