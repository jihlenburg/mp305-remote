/* Address: 0001f208; name: User_task; body bytes: 52 */

/* Confirmed by task-create function pointer and literal name User_task; calls dispatcher and
   companion transmit service. */

void User_task(void)

{
  FUN_000188e0();
  FUN_00014318();
  do {
    FUN_000658d4(1);
    FUN_000278a4();
    FUN_00014a98();
    FUN_00012d54();
    dispatch_command(1);
    service_companion_tx(1);
    FUN_0001d380();
    FUN_00012850();
    FUN_00019d14();
  } while( true );
}

