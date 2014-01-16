

float f1( qreal fi1, qreal fi2, qreal omega1, qreal omega2, qreal A, qreal B, qreal C ){

    return ((-0.5*sin(2*(fi1-fi2))*omega1*omega1 +C*sin(fi2)*cos(fi1-fi2) - B*sin(fi1-fi2)*omega2*omega2 - (A+1)*C*sin(fi1))/(A+sin(fi1-fi2)*sin(fi1-fi2)));
}

float f2( qreal fi1, qreal fi2, qreal omega1, qreal omega2, qreal A, qreal B, qreal C ){

    return (((A+1)*sin(fi1-fi2)*omega1*omega1 - (A+1)*C*sin(fi2) + B/2 * sin(2*(fi1-fi2))*omega2*omega2 + (A+1)*C*sin(fi1*cos(fi1-fi2)))/(B*(A+sin(fi1-fi2)*sin(fi1-fi2))));
}
