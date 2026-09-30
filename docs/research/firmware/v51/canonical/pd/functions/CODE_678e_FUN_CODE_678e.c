/* Address: CODE:678e; name: FUN_CODE_678e; body bytes: 113 */

byte FUN_CODE_678e(char *param_1,char param_2)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  FUN_CODE_9cf0();
  cVar1 = '\x02';
  FUN_CODE_8ecd();
  FUN_CODE_a733();
  FUN_CODE_342b(0xb3);
  *param_1 = '\0';
  FUN_CODE_33f5(cVar1 + -0x74);
  *param_1 = '\0';
  FUN_CODE_a6fd();
  FUN_CODE_349f();
  *param_1 = cVar1;
  FUN_CODE_8ac2();
  FUN_CODE_33d6();
  FUN_CODE_a9ae(0xdb,100);
  bVar2 = FUN_CODE_33e2(param_2 + '[');
  FUN_CODE_a99c(bVar2 | 0x40);
  FUN_CODE_33b9();
  FUN_CODE_a9ae(0xb,0x59);
  FUN_CODE_a9ae(8,0xe);
  bVar2 = FUN_CODE_33dc(0x7c,0xd);
  FUN_CODE_33d3(bVar2 | 0x20);
  FUN_CODE_a9ae(0,0x65);
  bVar3 = (&DAT_CODE_b8f0)[DAT_INTMEM_b3];
  bVar2 = DAT_SFR_c3;
  DAT_SFR_c3 = bVar2 & ~bVar3;
  bVar2 = FIFLG1;
  FIFLG1 = bVar2 | bVar3;
  return bVar3;
}

