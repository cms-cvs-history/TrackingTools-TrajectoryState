#include "TrackingTools/TrajectoryState/interface/TrajectoryStateClosestToBeamLine.h"

TrajectoryStateClosestToBeamLine::TrajectoryStateClosestToBeamLine
	(const FreeTrajectoryState& stateAtPCA, const GlobalPoint & pointOnBeamLine,
	 const reco::BeamSpot& beamSpot) :
	theFTS(stateAtPCA) , thePointOnBeamLine(pointOnBeamLine), theBeamSpot(beamSpot)
{}

Measurement1D TrajectoryStateClosestToBeamLine::transverseImpactParameter() const
{


  AlgebraicSymMatrix33 error = theBeamSpot.covariance3D() +
	theFTS.cartesianError().matrix().Sub<AlgebraicSymMatrix33>(0,0);

  GlobalPoint impactPoint=theFTS.position();
  AlgebraicVector3 transverseFlightPath(
	impactPoint.x()-thePointOnBeamLine.x(),impactPoint.y()-thePointOnBeamLine.y(),0.);
  double ipError = sqrt( ROOT::Math::Similarity(transverseFlightPath.Unit(),error) );
  return Measurement1D (ROOT::Math::Mag(transverseFlightPath), ipError);
}
