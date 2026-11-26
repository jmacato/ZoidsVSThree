extern void sDispPartnerAnim(void *arg);
extern void sDispOrderAnim(void *arg);

void dispAnim(void *arg)
{
    sDispPartnerAnim(arg);
    sDispOrderAnim(arg);
}
