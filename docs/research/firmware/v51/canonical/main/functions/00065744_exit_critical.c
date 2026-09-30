/* Address: 00065744; name: exit_critical; body bytes: 16 */

/* Decrements critical counter, clears BASEPRI when zero. */

void exit_critical(void)

{
  bool bVar1;
  
  DAT_1ffe0058 = DAT_1ffe0058 + -1;
  if ((DAT_1ffe0058 == 0) && (bVar1 = (bool)isCurrentModePrivileged(), bVar1)) {
    setBasePriority(0);
  }
  return;
}

