/* Address: ram:00055a44; name: FUN_ram_00055a44; body bytes: 184 */

void FUN_ram_00055a44(int param_1)

{
  undefined2 uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  
  uVar3 = DAT_ram_20001d8e;
  uVar2 = DAT_ram_20001d82;
  gp = 0x20004000;
  *(undefined2 *)(param_1 + 0x1c0) = 0x1b;
  *(undefined2 *)(param_1 + 0x1bc) = 0x1b;
  uVar4 = DAT_ram_20001d90;
  *(ushort *)(param_1 + 0x1b8) = uVar2;
  *(ushort *)(param_1 + 0x1b4) = uVar3;
  *(ushort *)(param_1 + 0x1b6) = uVar4;
  if (*(char *)(param_1 + 0x147) == '\x02') {
    uVar5 = 0xa90;
  }
  else {
    uVar5 = 0x148;
  }
  *(ushort *)(param_1 + 0x1c2) = uVar5;
  if (*(char *)(param_1 + 0x146) == '\x02') {
    *(undefined2 *)(param_1 + 0x1ba) = DAT_ram_20001d88;
    uVar1 = 0xa90;
  }
  else {
    *(undefined2 *)(param_1 + 0x1ba) = DAT_ram_20001d86;
    uVar1 = 0x148;
  }
  *(undefined2 *)(param_1 + 0x1be) = uVar1;
  if (0x1b < uVar2) {
    uVar2 = 0x1b;
  }
  *(ushort *)(param_1 + 0x1c8) = uVar2;
  if (0x1b < uVar3) {
    uVar3 = 0x1b;
  }
  *(ushort *)(param_1 + 0x1c4) = uVar3;
  uVar3 = *(ushort *)(param_1 + 0x1be);
  if (*(ushort *)(param_1 + 0x1ba) < *(ushort *)(param_1 + 0x1be)) {
    uVar3 = *(ushort *)(param_1 + 0x1ba);
  }
  *(ushort *)(param_1 + 0x1ca) = uVar3;
  if (uVar5 < uVar4) {
    uVar4 = uVar5;
  }
  *(ushort *)(param_1 + 0x1c6) = uVar4;
  *(char *)(param_1 + 0x4c) = (char)uVar2;
  return;
}

