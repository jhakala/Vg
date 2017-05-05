def getMasses(kind = "all"):
  if kind=="all":
    masses=[]
    mass = 700
    while mass <=3250:
      masses.append(mass)
      mass += 10
    return masses
  elif kind=="fullsim":
    return [650, 750, 850, 1000, 1150, 1300, 1450, 1600, 1750, 1900, 2050, 2450, 2850, 3250]
