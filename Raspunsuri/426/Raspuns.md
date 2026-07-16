STRETCH — What min, max frequency would have the signal on LED0 toggled from within ISR in case of min, max prescalers? FREQ MIN => _ FREQ MAX => _


## Raspuns ##
Din ce am citit ni se cere frecventa de toggle,asta inseamna cate toggle-uri au loc intr-o secunda
formula este : Fclock/(prescale*256)
Frecventa minima e caracterizata de prescale-ul cel mai mare :
1000000Hz/(1024*256)=3.81 HZ
Frecventa maxima e caracterizata de prescale-ul cea mai mare:
1000000Hz/(1*256)=3906.25 HZ
