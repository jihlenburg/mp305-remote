/* Address: ram:000035a8; name: encode_transport_frame; body bytes: 186 */

/* Confirmed in code: AA stuffing and additive checksum. */

int encode_transport_frame(undefined4 param_1,char *param_2,undefined1 *param_3)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  char *pcVar5;
  byte bVar6;
  char cVar7;
  
  gp = &DAT_ram_20002000;
  cVar7 = *param_2;
  bVar1 = param_2[1];
  bVar6 = cVar7 << 4 | bVar1 & 0xf;
  *param_3 = 0xaa;
  param_3[1] = cVar7 << 4 | bVar1 & 0xf;
  if (bVar6 == 0xaa) {
    pcVar3 = param_3 + 3;
    param_3[2] = 0xaa;
  }
  else {
    pcVar3 = param_3 + 2;
  }
  cVar7 = param_2[2];
  *pcVar3 = cVar7;
  if (cVar7 == -0x56) {
    pcVar5 = pcVar3 + 2;
    pcVar3[1] = -0x56;
  }
  else {
    pcVar5 = pcVar3 + 1;
  }
  cVar7 = bVar6 + param_2[2];
  uVar4 = 0;
  while( true ) {
    pcVar3 = pcVar5 + 1;
    if (*(ushort *)(param_2 + 2) <= uVar4) break;
    cVar2 = param_2[uVar4 + 4];
    cVar7 = cVar7 + cVar2;
    *pcVar5 = cVar2;
    if (cVar2 == -0x56) {
      pcVar3 = pcVar5 + 2;
      pcVar5[1] = -0x56;
    }
    uVar4 = uVar4 + 1 & 0xff;
    pcVar5 = pcVar3;
  }
  *pcVar5 = cVar7;
  if (cVar7 == -0x56) {
    pcVar3 = pcVar5 + 2;
    pcVar5[1] = -0x56;
  }
  return (int)pcVar3 - (int)param_3;
}

