/* Address: 000277f0; name: FUN_000277f0; body bytes: 172 */

undefined4 FUN_000277f0(byte *param_1,undefined1 *param_2,ushort *param_3,ushort *param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  
  iVar2 = FUN_000375ec();
  iVar3 = 0;
  if (((DAT_1fff8e97 != '\0') || (2 < DAT_1fff8e98)) && (DAT_1fff8e9c == '\0')) {
    iVar3 = 1;
  }
  *param_1 = (byte)(&DAT_1fff8e99)[-iVar3] >> 4;
  *param_2 = (&DAT_1fff8e98)[-iVar3];
  uVar4 = (ushort)(byte)(&DAT_1fff8e9c)[-iVar3] + ((byte)(&DAT_1fff8e9b)[-iVar3] & 0xf) * 0x100;
  uVar1 = (ushort)(byte)(&DAT_1fff8e9a)[-iVar3] + ((byte)(&DAT_1fff8e99)[-iVar3] & 0xf) * 0x100;
  if ((0xf0 < uVar4) || (0x140 < uVar1)) {
    DAT_1ffe0150 = DAT_1ffe0150 + 1;
    return 1;
  }
  if (iVar2 != 0) {
    if (iVar2 == 1) {
      *param_3 = uVar1;
      *param_4 = uVar4;
      return 0;
    }
    if (iVar2 == 2) {
      *param_3 = uVar4;
      uVar1 = 0x140 - uVar1;
      goto LAB_0002788a;
    }
    if (iVar2 == 3) {
      *param_3 = 0x140 - uVar1;
      uVar1 = 0xf0 - uVar4;
      goto LAB_0002788a;
    }
  }
  *param_3 = 0xf0 - uVar4;
LAB_0002788a:
  *param_4 = uVar1;
  return 0;
}

