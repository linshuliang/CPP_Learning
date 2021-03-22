double power(double base, int component)
{
  int ret = base;
  if(component == 0)
    return 1;

  for(int i=1; i<component; i++)
    ret = ret * base;

  return ret;
}
