/* Address: ram:00003662; name: decode_transport_byte; body bytes: 194 */

/* Confirmed in code: stateful AA-stuffed stream decoder. */

undefined1 * decode_transport_byte(undefined1 *param_1,uint param_2)

{
  undefined1 *puVar1;
  byte bVar2;
  byte bVar3;
  undefined4 uVar4;
  uint uVar5;
  
  gp = &DAT_ram_20002000;
  bVar2 = (byte)param_2;
  if (param_2 == 0xaa) {
    bVar3 = param_1[0x214] + 1;
    param_1[0x214] = bVar3;
    if ((bVar3 & 1) != 0) {
      return (undefined1 *)0x0;
    }
LAB_ram_000036a6:
    switch(*(undefined4 *)(param_1 + 0x20c)) {
    case 0:
      goto switchD_ram_000036c0_caseD_0;
    case 1:
      goto switchD_ram_000036c0_caseD_1;
    default:
switchD_ram_000036c0_caseD_2:
      *(undefined4 *)(param_1 + 0x20c) = 0;
      return (undefined1 *)0x0;
    case 4:
      if (param_2 == 0) goto switchD_ram_000036c0_caseD_2;
      *(short *)(param_1 + 2) = (short)param_2;
      param_1[0x210] = 0;
      param_1[0x211] = bVar2 + param_1[0x211];
      uVar4 = 6;
      break;
    case 6:
      bVar3 = param_1[0x210];
      param_1[bVar3 + 4] = bVar2;
      uVar5 = bVar3 + 1;
      param_1[0x211] = bVar2 + param_1[0x211];
      param_1[0x210] = (char)uVar5;
      if ((uVar5 & 0xff) < (uint)*(ushort *)(param_1 + 2)) {
        return (undefined1 *)0x0;
      }
      uVar4 = 7;
      break;
    case 7:
      puVar1 = (undefined1 *)0x0;
      if ((byte)param_1[0x211] == param_2) {
        param_1[0x208] = 1;
        puVar1 = param_1;
      }
      *(undefined4 *)(param_1 + 0x20c) = 0;
      return puVar1;
    }
  }
  else {
    if ((param_1[0x214] & 1) == 0) goto LAB_ram_000036a6;
    param_1[0x214] = 0;
switchD_ram_000036c0_caseD_1:
    param_1[1] = bVar2 & 0xf;
    *param_1 = (char)(param_2 >> 4);
    param_1[0x211] = bVar2;
    uVar4 = 4;
  }
  *(undefined4 *)(param_1 + 0x20c) = uVar4;
switchD_ram_000036c0_caseD_0:
  return (undefined1 *)0x0;
}

