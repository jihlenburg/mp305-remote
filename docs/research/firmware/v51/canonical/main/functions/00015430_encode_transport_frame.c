/* Address: 00015430; name: encode_transport_frame; body bytes: 110 */

int encode_transport_frame(int param_1,char *param_2,undefined1 *param_3)

{
  char cVar1;
  char cVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  int extraout_r3;
  int extraout_r3_00;
  int extraout_r3_01;
  byte bVar6;
  uint uVar7;
  
  puVar3 = &DAT_1fff9be4 + param_1 * 0x214;
  bVar6 = param_2[1] & 0xfU | *param_2 << 4;
  *param_3 = 0xaa;
  uVar4 = append_stuffed_byte(puVar3,bVar6,param_3 + 1,param_2);
  uVar4 = append_stuffed_byte(puVar3,*(undefined1 *)(extraout_r3 + 2),uVar4);
  cVar2 = *(char *)(extraout_r3_00 + 2) + bVar6;
  iVar5 = extraout_r3_00;
  for (uVar7 = 0; uVar7 < *(byte *)(iVar5 + 2); uVar7 = uVar7 + 1) {
    cVar1 = *(char *)(iVar5 + uVar7 + 4);
    cVar2 = cVar2 + cVar1;
    uVar4 = append_stuffed_byte(puVar3,cVar1,uVar4);
    iVar5 = extraout_r3_01;
  }
  iVar5 = append_stuffed_byte(puVar3,cVar2,uVar4);
  return iVar5 - (int)param_3;
}

