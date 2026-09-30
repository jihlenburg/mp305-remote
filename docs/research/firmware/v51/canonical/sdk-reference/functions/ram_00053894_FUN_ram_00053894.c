/* Address: ram:00053894; name: FUN_ram_00053894; body bytes: 68 */

void FUN_ram_00053894(int param_1)

{
  char cVar1;
  char cVar2;
  
  gp = 0x20004000;
  cVar1 = *(char *)(param_1 + 0x1a);
  if ((cVar1 != '\0') && (*(char *)(param_1 + 10) == cVar1)) {
LAB_ram_000538a2:
    FUN_ram_00053848();
    return;
  }
  cVar2 = *(char *)(param_1 + 0x19);
  if (cVar2 == '\0') {
    if ((cVar1 == '\0') || (*(char *)(param_1 + 10) != '\0')) goto LAB_ram_000538a2;
  }
  else {
    if (*(char *)(param_1 + 10) != cVar2) {
      *(char *)(param_1 + 10) = cVar2;
      goto LAB_ram_000538b8;
    }
    if (cVar1 == '\0') goto LAB_ram_000538a2;
  }
  *(char *)(param_1 + 10) = cVar1;
LAB_ram_000538b8:
  tmos_set_event(DAT_ram_20001b67,2);
  return;
}

