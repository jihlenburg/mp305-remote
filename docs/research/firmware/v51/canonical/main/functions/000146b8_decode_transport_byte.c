/* Address: 000146b8; name: decode_transport_byte; body bytes: 196 */

/* Byte-stream parser. Pairwise AA stuffing, additive checksum. Verified offline with original
   instructions. */

undefined * decode_transport_byte(int param_1,uint param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined *puVar3;
  byte bVar4;
  
  param_1 = param_1 * 0x214;
  puVar3 = (undefined *)0x0;
  if (param_2 == 0xaa) {
    bVar4 = (&DAT_1fff9df7)[param_1] + 1;
    (&DAT_1fff9df7)[param_1] = bVar4;
    if ((bVar4 & 1) != 0) {
      return (undefined *)0x0;
    }
  }
  else {
    if (((&DAT_1fff9df7)[param_1] & 1) != 0) {
      (&DAT_1fff9dec)[param_1] = 1;
    }
    (&DAT_1fff9df7)[param_1] = 0;
  }
  bVar4 = (byte)param_2;
  switch((&DAT_1fff9dec)[param_1]) {
  case 0:
    goto switchD_0001ff5c_caseD_0;
  case 1:
    (&DAT_1fff9dec)[param_1] = 2;
    (&DAT_1fff9be5)[param_1] = bVar4 & 0xf;
    (&DAT_1fff9be4)[param_1] = (char)(param_2 >> 4);
    (&DAT_1fff9df4)[param_1] = bVar4;
    return (undefined *)0x0;
  case 2:
    *(undefined4 *)(&DAT_1fff9df0 + param_1) = 0;
    (&DAT_1fff9be6)[param_1] = bVar4;
    (&DAT_1fff9df4)[param_1] = bVar4 + (&DAT_1fff9df4)[param_1];
    uVar1 = 3;
LAB_0001ffc2:
    (&DAT_1fff9dec)[param_1] = uVar1;
    return (undefined *)0x0;
  case 3:
    *(byte *)(*(int *)(&DAT_1fff9df0 + param_1) + param_1 + 0x1fff9be8) = bVar4;
    (&DAT_1fff9df4)[param_1] = bVar4 + (&DAT_1fff9df4)[param_1];
    iVar2 = *(int *)(&DAT_1fff9df0 + param_1);
    *(uint *)(&DAT_1fff9df0 + param_1) = iVar2 + 1U;
    if ((uint)(byte)(&DAT_1fff9be6)[param_1] <= iVar2 + 1U) {
      uVar1 = 4;
      goto LAB_0001ffc2;
    }
switchD_0001ff5c_caseD_0:
    if ((&DAT_1fff9dec)[param_1] == '\x05') {
LAB_0001ffe6:
      (&DAT_1fff9dec)[param_1] = 0;
      puVar3 = &DAT_1fff9be4 + param_1;
    }
    return puVar3;
  case 4:
    if ((byte)(&DAT_1fff9df4)[param_1] != param_2) goto switchD_0001ff5c_default;
    (&DAT_1fff9dec)[param_1] = 5;
    goto LAB_0001ffe6;
  default:
switchD_0001ff5c_default:
    (&DAT_1fff9dec)[param_1] = 0;
    return (undefined *)0x0;
  }
}

