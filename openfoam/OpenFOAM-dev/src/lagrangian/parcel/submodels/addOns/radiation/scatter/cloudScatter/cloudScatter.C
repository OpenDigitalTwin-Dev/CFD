/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2024 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "cloudScatter.H"
#include "addToRunTimeSelectionTable.H"
#include "parcelCloud.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace radiationModels
{
namespace scatterModels
{
    defineTypeNameAndDebug(cloud, 0);

    addToRunTimeSelectionTable
    (
        scatterModel,
        cloud,
        dictionary
    );
}
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::radiationModels::scatterModels::cloud::cloud
(
    const dictionary& dict,
    const fvMesh& mesh
)
:
    scatterModel(dict, mesh),
    coeffDict_(dict.subDict(typeName + "Coeffs")),
    cloudNames_(coeffDict_.lookup("cloudNames"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::radiationModels::scatterModels::cloud::~cloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::radiationModels::scatterModels::cloud::sigmaEff() const
{
    tmp<volScalarField> tsigma
    (
        volScalarField::New
        (
            "sigma",
            mesh_,
            dimensionedScalar(dimless/dimLength, 0)
        )
    );

    forAll(cloudNames_, i)
    {
        const parcelCloud& tc =
            mesh_.objectRegistry::lookupObject<parcelCloud>(cloudNames_[i]);

        tsigma.ref() += tc.sigmap();
    }

    return 3.0*tsigma;
}


// ************************************************************************* //
