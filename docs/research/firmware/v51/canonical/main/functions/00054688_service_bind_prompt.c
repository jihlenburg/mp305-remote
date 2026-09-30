/* Address: 00054688; name: service_bind_prompt; body bytes: 130 */

/* Main UI bind-prompt state machine. May decline when a different screen is active. */

void service_bind_prompt(void)

{
  int iVar1;
  
  if ((((DAT_1ffe0330 == DAT_1ffe0468) || (DAT_1ffe0330 == DAT_1ffe068c)) ||
      (DAT_1ffe0330 == DAT_1ffe06a0)) ||
     ((DAT_1ffe0248 != '\0' || (iVar1 = FUN_00040928(0), iVar1 != DAT_1ffe0344)))) {
    iVar1 = FUN_00040928(0);
    if ((iVar1 != DAT_1ffe0344) && (bind_pending != '\0')) {
      bind_decision = 0;
      bind_pending = '\0';
      DAT_1fff9550 = DAT_1fff9550 | 2;
    }
    return;
  }
  if (bind_pending == '\0') {
    return;
  }
  if (DAT_1ffe0247 == '\0') {
    FUN_0005efd8();
    bind_pending = 0;
    return;
  }
  FUN_0001ba58();
  return;
}

