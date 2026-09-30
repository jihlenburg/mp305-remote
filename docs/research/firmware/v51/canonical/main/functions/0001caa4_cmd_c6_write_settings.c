/* Address: 0001caa4; name: cmd_c6_write_settings; body bytes: 226 */

undefined4 cmd_c6_write_settings(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  undefined4 uVar3;
  
  cVar2 = '\0';
  *param_3 = *param_1 + '\x01';
  bVar1 = param_1[1];
  if (0x14 < (byte)param_1[1] - 0x50) {
    cVar2 = -1;
    bVar1 = DAT_1fffaaf9;
  }
  DAT_1fffaaf9 = bVar1;
  if ((cVar2 == '\0') && ((byte)param_1[2] < 4)) {
    cVar2 = '\0';
    DAT_1fffaafe = param_1[2];
  }
  else {
    cVar2 = -1;
  }
  if ((cVar2 == '\0') && ((byte)param_1[3] < 2)) {
    cVar2 = '\0';
    DAT_1fffaafa = param_1[3];
  }
  else {
    cVar2 = -1;
  }
  if ((cVar2 == '\0') && ((byte)param_1[4] < 0x1f)) {
    cVar2 = '\0';
    DAT_1fffaaff = param_1[4];
  }
  else {
    cVar2 = -1;
  }
  if ((cVar2 != '\0') || (cVar2 = '\0', 1 < (byte)param_1[5])) {
    cVar2 = -1;
  }
  if ((cVar2 == '\0') && (*(ushort *)(param_1 + 6) < 0x3e9)) {
    cVar2 = '\0';
    DAT_1fffab62 = *(ushort *)(param_1 + 6);
  }
  else {
    cVar2 = -1;
  }
  if ((cVar2 == '\0') && (*(ushort *)(param_1 + 8) < 0x3e9)) {
    cVar2 = '\0';
    DAT_1fffab64 = *(ushort *)(param_1 + 8);
  }
  else {
    cVar2 = -1;
  }
  if ((cVar2 == '\0') && ((byte)param_1[10] < 2)) {
    cVar2 = '\0';
    DAT_1fffab01 = param_1[10];
  }
  else {
    cVar2 = -1;
  }
  if ((cVar2 == '\0') && ((byte)param_1[0xb] < 2)) {
    cVar2 = '\0';
    DAT_1fffab02 = param_1[0xb];
  }
  else {
    cVar2 = -1;
  }
  if ((cVar2 == '\0') && (*(ushort *)(param_1 + 0xc) < 0x3e9)) {
    settings_dirty = 1;
    cVar2 = '\0';
    DAT_1fffab70 = *(ushort *)(param_1 + 0xc);
  }
  else {
    cVar2 = -1;
  }
  param_3[1] = cVar2;
  uVar3 = 2;
  if (param_4 == 6) {
    uVar3 = 3;
    param_3[2] = param_1[param_2 + -1];
  }
  return uVar3;
}

